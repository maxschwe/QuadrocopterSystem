#include "drone.h"

#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include "esp_mac.h"

#include "MPU6050.h"
#include "MPU6050_6Axis_MotionApps20.h"

#include "rotor.h"
#include "esc_timer.h"

const char* TAG = "Drone";

const gpio_num_t PIN_SDA = (gpio_num_t)21;
const gpio_num_t PIN_CLK = (gpio_num_t)22;


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
    bool mpuSuccess = initMpu(mpu_interrupt_pin);

    if (!mpuSuccess) {
        ESP_LOGE(TAG, "Failed to initialize MPU6050. Halting execution.");
        while (true) {
            vTaskDelay(pdMS_TO_TICKS(1000)); // Halt execution
        }
    }

    initRotors();
    
    ESP_LOGI(TAG, "Setup Complete");
}


bool Drone::initMpu(gpio_num_t mpu_interrupt_pin) {
    ESP_LOGI(TAG, "Initializing MPU6050...");

    mpuMailbox = xQueueCreate(1, sizeof(VectorFloat));
    initI2C();

    mpu = MPU6050();
	mpu.initialize();

    if (!mpu.testConnection()) {
        ESP_LOGE(TAG, "MPU6050 connection test failed!");
        return false; // Return failure
    }

	mpu.dmpInitialize();

	// This need to be setup individually
	// mpu.setXGyroOffset(220);
	// mpu.setYGyroOffset(76);
	// mpu.setZGyroOffset(-85);
	// mpu.setZAccelOffset(1788);
    
    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);

	mpu.setDMPEnabled(true);

    xTaskCreate(this->wrapperMPUInterruptProcessor, "mpu_processor", 4096, this, 10, &(this->mpuProcessingTaskHandle));

    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_POSEDGE; // Rising Edge
    io_conf.pin_bit_mask = (1ULL << mpu_interrupt_pin);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE; // MPU6050 INT pin is usually Push-Pull or Open Drain active high
    gpio_config(&io_conf);

    // Install ISR service and Attach Handler
    gpio_install_isr_service(0);
    gpio_isr_handler_add(mpu_interrupt_pin, wrapperOnMpuInterrupt, this);

    ESP_LOGI(TAG, "MPU6050 initialized.");
    return true;
}

void Drone::wrapperOnMpuInterrupt(void *drone) {
    static_cast<Drone*>(drone)->onMpuInterrupt();
}

void Drone::onMpuInterrupt() {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    // Notify the processing task that an interrupt occurred.
    // This increments the task's notification value.
    vTaskNotifyGiveFromISR(this->mpuProcessingTaskHandle, &xHigherPriorityTaskWoken);

    // If waking the task changes the scheduler priority, run scheduler immediately and
    // switch to the woken up task immediately.
    if (xHigherPriorityTaskWoken == pdTRUE) {
        portYIELD_FROM_ISR();
    }
}

void IRAM_ATTR Drone::wrapperMPUInterruptProcessor(void *drone) {
    static_cast<Drone*>(drone)->mpuInterruptProcessor();
}

void IRAM_ATTR Drone::mpuInterruptProcessor() {
    ESP_LOGI(TAG, "Starting MPU Interrupt Processor Task...");

    const float RAD_TO_DEG = 180.0f / M_PI;

    while (1) {
        // Wait until notified of an interrupt
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        Quaternion q;
        VectorInt16 accel;

        VectorFloat gravity;
        float ypr[3];
        uint16_t packetSize = 42;   // expected DMP packet size (default is 42 bytes)
        uint8_t fifoBuffer[64];     // FIFO storage buffer
        uint8_t mpuIntStatus = mpu.getIntStatus();    // holds actual interrupt status byte from MPU
        uint16_t fifoCount = mpu.getFIFOCount();

        if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
            // reset because in this case FIFO overflowed, so now
            // there's new data in the lower addresses and old data in the higher addresses
            // you can't know which data is old and which is new
            mpu.resetFIFO();
            ESP_LOGW("MPU6050", "FIFO overflowed, Resetting it (Int Status: %x)", mpuIntStatus);
        }

        if (!(mpuIntStatus & 0x02) || fifoCount < packetSize) {
            // otherwise, if it's not a DMP data ready interrupt or fifo count is to small skip the count
            ESP_LOGW("MPU6050", "FIFO content to small or wrong interrupt (Int Status: %x)", mpuIntStatus);
            continue;
        }

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

        VectorFloat rpy_vec(ypr[2] * RAD_TO_DEG, ypr[1] * RAD_TO_DEG, ypr[0] * RAD_TO_DEG);

        xQueueOverwrite(mpuMailbox, &rpy_vec);
    }
}

void Drone::initRotors() {
    ESP_LOGI(TAG, "Initializing rotors...");
    setThrottles(0.0f, 0.0f, 0.0f, 0.0f);
    vTaskDelay(pdMS_TO_TICKS(2500));
    ESP_LOGI(TAG, "Rotors initialized.");
}

VectorFloat Drone::rpy() {
    VectorFloat rpy;
    if (xQueuePeek(mpuMailbox, &rpy, 0)) {
        return rpy;
    }

    ESP_LOGW(TAG, "Failed to peek data from MPU mailbox.");
    return VectorFloat(0.0f, 0.0f, 0.0f);
}

void Drone::printRpy() {
    VectorFloat rpy = this->rpy();
    printf("Roll: %f, Pitch: %f, Yaw: %f\n", rpy.x, rpy.y, rpy.z);
}

void Drone::setThrottles(float throttle1, float throttle2, float throttle3, float throttle4) {
    rotor1.setThrottle(throttle1);
    rotor2.setThrottle(throttle2);
    rotor3.setThrottle(throttle3);
    rotor4.setThrottle(throttle4);
}
