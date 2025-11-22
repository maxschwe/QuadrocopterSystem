#include "drone.h"

#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

#include "MPU6050.h"
#include "MPU6050_6Axis_MotionApps20.h"

#include "rotor.h"
#include "esc_timer.h"


const gpio_num_t PIN_SDA = (gpio_num_t)21;
const gpio_num_t PIN_CLK = (gpio_num_t)22;

TaskHandle_t processingTaskHandle = NULL;
MPU6050 mpu;
QueueHandle_t mpuMailbox = NULL;

void initI2C() {
	i2c_config_t conf;
	conf.mode = I2C_MODE_MASTER;
	conf.sda_io_num = PIN_SDA;
	conf.scl_io_num = PIN_CLK;
	conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
	conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
	conf.master.clk_speed = 400000;
    conf.clk_flags = 0;
	ESP_ERROR_CHECK(i2c_param_config(I2C_NUM_0, &conf));
	ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0));
}


static void IRAM_ATTR gpio_isr_handler(void* arg) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    // Notify the processing task that an interrupt occurred.
    // This increments the task's notification value.
    vTaskNotifyGiveFromISR(processingTaskHandle, &xHigherPriorityTaskWoken);

    // If waking the task changes the scheduler priority, run scheduler immediately and
    // switch to the woken up task immediately.
    if (xHigherPriorityTaskWoken == pdTRUE) {
        portYIELD_FROM_ISR();
    }
}

void mpu_receive_task(void* params) {
    while (1) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        Quaternion q;           // [w, x, y, z]         quaternion container

        VectorInt16 accel;

        VectorFloat gravity;    // [x, y, z]            gravity vector
        float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
        uint16_t packetSize = 42;    // expected DMP packet size (default is 42 bytes)
        uint16_t fifoCount;     // count of all bytes currently in FIFO
        uint8_t fifoBuffer[64]; // FIFO storage buffer
        uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU

        do {
            mpuIntStatus = mpu.getIntStatus();
            fifoCount = mpu.getFIFOCount();

            if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
                // reset because in this case FIFO overflowed, so now
                // there's new data in the lower addresses and old data in the higher addresses
                // you can't know which data is old and which is new
                mpu.resetFIFO();
                ESP_LOGW("MPU6050", "FIFO overflowed, Resetting it (Int Status: %x)", mpuIntStatus);
            }
        } while (!(mpuIntStatus & 0x02));

        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

        VectorFloat ypr_vec(ypr[2]* 180/M_PI, ypr[1] * 180/M_PI, ypr[0] * 180/M_PI);

        xQueueOverwrite(mpuMailbox, &ypr_vec);
    }

    vTaskDelete(NULL);
}


Drone::Drone(
    ledc_timer_t timer_num,
    gpio_num_t rotor1_pin, ledc_channel_t rotor1_channel,
    gpio_num_t rotor2_pin, ledc_channel_t rotor2_channel,
    gpio_num_t rotor3_pin, ledc_channel_t rotor3_channel,
    gpio_num_t rotor4_pin, ledc_channel_t rotor4_channel,
    gpio_num_t mpu_interrupt_pin) : 
            esc_timer(timer_num),
            rotor1(rotor1_pin, rotor1_channel, this->esc_timer),
            rotor2(rotor2_pin, rotor2_channel, this->esc_timer),
            rotor3(rotor3_pin, rotor3_channel, this->esc_timer),
            rotor4(rotor4_pin, rotor4_channel, this->esc_timer)
{
    mpuMailbox = xQueueCreate(1, sizeof(VectorFloat));

    initI2C();

    mpu = MPU6050();
	mpu.initialize();
	mpu.dmpInitialize();

	// This need to be setup individually
	// mpu.setXGyroOffset(220);
	// mpu.setYGyroOffset(76);
	// mpu.setZGyroOffset(-85);
	// mpu.setZAccelOffset(1788);
    
    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);

	mpu.setDMPEnabled(true);

    rotor1.setThrottle(0.0f);
    rotor2.setThrottle(0.0f);
    rotor3.setThrottle(0.0f);
    rotor4.setThrottle(0.0f);
    vTaskDelay(pdMS_TO_TICKS(3000));

    xTaskCreate(&mpu_receive_task, "mpu_receive_task", 4096, this, 10, &processingTaskHandle);

    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_POSEDGE; // Rising Edge
    io_conf.pin_bit_mask = (1ULL << mpu_interrupt_pin);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE; // MPU6050 INT pin is usually Push-Pull or Open Drain active high
    gpio_config(&io_conf);

    // Install ISR service and Attach Handler
    gpio_install_isr_service(0);
    gpio_isr_handler_add(mpu_interrupt_pin, gpio_isr_handler, NULL);
    
    ESP_LOGI("Drone", "Setup Complete. Waiting for interrupts...");
}

VectorFloat Drone::ypr() {
    VectorFloat ypr;
    if (xQueuePeek(mpuMailbox, &ypr, 0)) {
        return ypr;
    }

    ESP_LOGW("Drone", "Failed to peek data from MPU mailbox.");
    return VectorFloat(0.0f, 0.0f, 0.0f);
}
