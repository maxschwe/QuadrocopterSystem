#include "drone.h"

#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <numbers>
#include "esp_mac.h"
#include <string.h>
#include "driver/uart.h"

#include "MPU6050.h"
#include "MPU6050_6Axis_MotionApps20.h"

#include "rotor.h"
#include "esc_timer.h"

#define UART_NUM UART_NUM_2
#define RX_BUF_SIZE 1024
#define TIMEOUT_UART 20
#define FRAME_SIZE 16
#define FRAME_1_TYPE 0x54
#define FRAME_2_TYPE 0x5c

#define RECEIVER_MIN 343
#define RECEIVER_MAX 1705

#define DEGREES_TO_RADIANS 0.01745329252

#define THROTTLE_MIN_MAP 2
#define THROTTLE_MAX_MAP 10
#define YAW_MIN_MAP 180 * DEGREES_TO_RADIANS
#define YAW_MAX_MAP -180 * DEGREES_TO_RADIANS
#define PITCH_MIN_MAP 20 * DEGREES_TO_RADIANS
#define PITCH_MAX_MAP -20 * DEGREES_TO_RADIANS
#define ROLL_MIN_MAP 20 * DEGREES_TO_RADIANS
#define ROLL_MAX_MAP -20 * DEGREES_TO_RADIANS

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
    gpio_num_t mpu_interrupt_pin, bool remote_control_enabled) : 
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

    if (remote_control_enabled) {
        startRemoteControlReceiver();
    }    

    initRotors();
    
    ESP_LOGI(TAG, "Setup Complete");

    startPosition = PositionData{0.0f, 0.0f, 0.0f, 0};
    position = PositionData{0.0f, 0.0f, 0.0f, 0};
}


bool Drone::initMpu(gpio_num_t mpu_interrupt_pin) {
    ESP_LOGI(TAG, "Initializing MPU6050...");

    initI2C();
    
    mpu = MPU6050();
	mpu.initialize();
    
    if (!mpu.testConnection()) {
        ESP_LOGE(TAG, "MPU6050 connection test failed!");
        return false;
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

    uint8_t gyro_fs = mpu.getFullScaleGyroRange();

    ESP_LOGI(TAG, "Gyro Full Scale Range Mode");

    // Decode the number:
    if (gyro_fs == 0) ESP_LOGI(TAG, "+/- 250 deg/s (Divisor: 131.0)");
    if (gyro_fs == 1) ESP_LOGI(TAG, "+/- 500 deg/s (Divisor: 65.5)");
    if (gyro_fs == 2) ESP_LOGI(TAG, "+/- 1000 deg/s (Divisor: 32.8)");
    if (gyro_fs == 3) ESP_LOGI(TAG, "+/- 2000 deg/s (Divisor: 16.4)");
    
    this->mpuMailbox = xQueueCreate(1, sizeof(OrientationData));
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

        int16_t raw_gyro[3];
        mpu.dmpGetGyro(raw_gyro, fifoBuffer);

        OrientationData orientation; // Roll, Pitch, Yaw
        orientation.roll = ypr[2];

        // negating these because the data you get from the DMP is in the NED (North-East-Down) convention, but we want to use (North-West-Down) convention for our controller
        orientation.pitch = -ypr[1];
        orientation.yaw = -ypr[0];

        float gyro_x_body = raw_gyro[0] / 16.4 * DEGREES_TO_RADIANS;
        float gyro_y_body = raw_gyro[1] / 16.4 * DEGREES_TO_RADIANS;
        float gyro_z_body = raw_gyro[2] / 16.4 * DEGREES_TO_RADIANS;

        orientation.roll_rate = gyro_x_body + sin(orientation.roll) * tan(orientation.pitch) * gyro_y_body +
                                cos(orientation.roll) * tan(orientation.pitch) * gyro_z_body;
        orientation.pitch_rate = cos(orientation.roll) * gyro_y_body - sin(orientation.roll) * gyro_z_body;
        orientation.yaw_rate = sin(orientation.roll) / cos(orientation.pitch) * gyro_y_body + 
                               cos(orientation.roll) / cos(orientation.pitch) * gyro_z_body;

        orientation.lastUpdate = xTaskGetTickCount();

        xQueueOverwrite(mpuMailbox, &orientation);
    }
}

void Drone::initRotors() {
    ESP_LOGI(TAG, "Initializing rotors...");
    setThrottles(0.0f, 0.0f, 0.0f, 0.0f);
    vTaskDelay(pdMS_TO_TICKS(2500));
    ESP_LOGI(TAG, "Rotors initialized.");
}

OrientationData Drone::orientation() {
    OrientationData orientation;
    if (xQueuePeek(mpuMailbox, &orientation, 0)) {
        return orientation;
    }

    ESP_LOGW(TAG, "Failed to peek data from MPU mailbox.");
    return OrientationData{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0};
}

void Drone::printRpy() {
    OrientationData orientation = this->orientation();
    printf("Roll: %f, Pitch: %f, Yaw: %f\n", orientation.roll, orientation.pitch, orientation.yaw);
}

void Drone::setThrottles(float throttle1, float throttle2, float throttle3, float throttle4) {
    rotor1.setThrottle(throttle1);
    rotor2.setThrottle(throttle2);
    rotor3.setThrottle(throttle3);
    rotor4.setThrottle(throttle4);
}

static uint16_t decode_channel(uint8_t msb, uint8_t lsb) {
    return ((msb & 0x07) << 8) | lsb;
}

static float lin_map(uint16_t val, float out_min, float out_max) {
    return out_min + (float)(val - RECEIVER_MIN) * (out_max - out_min) / (RECEIVER_MAX - RECEIVER_MIN);
}

void Drone::startRemoteControlReceiver() {
    uart_config_t uart_config = {
        .baud_rate = 115200,        // SRXL usually ~115200s
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 0,
        .source_clk = UART_SCLK_APB,
    };

    ESP_ERROR_CHECK(uart_driver_install(UART_NUM, RX_BUF_SIZE, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(UART_NUM, &uart_config));

    ESP_ERROR_CHECK(uart_set_pin(
        UART_NUM,
        UART_PIN_NO_CHANGE,  // TX not used
        16,                  // RX pin (change if needed)
        UART_PIN_NO_CHANGE,
        UART_PIN_NO_CHANGE
    ));

    xTaskCreate(this->wrapperRemoteControlReceiver, "remote_control_receiver", 4096, this, 3, NULL);
}

ReferenceInputs& Drone::getReferenceInputs() {
    return this->w;
}

void Drone::wrapperRemoteControlReceiver(void *drone) {
    static_cast<Drone*>(drone)->remoteControlReceiver();
}

void Drone::processFrame(uint8_t* frame) {
    uint8_t frame_type = frame[12]; // 13th byte
    if (frame_type == 0x54) {
        uint16_t roll_val = decode_channel(frame[2], frame[3]); // Channel 1
        uint16_t pitch_val = decode_channel(frame[6], frame[7]); // Channel 2
        uint16_t throttle_val = decode_channel(frame[4], frame[5]); // Channel 3

        float throttle = lin_map(throttle_val, THROTTLE_MIN_MAP, THROTTLE_MAX_MAP);
        float roll = lin_map(roll_val, ROLL_MIN_MAP, ROLL_MAX_MAP);
        float pitch = lin_map(pitch_val, PITCH_MIN_MAP, PITCH_MAX_MAP);

        this->w.roll = roll;
        this->w.pitch = pitch;
        this->w.throttle = throttle;
        
        this->w.lastUpdate = xTaskGetTickCount();
    } else if (frame_type == 0x5C) {
        uint16_t yaw_val = decode_channel(frame[6], frame[7]); // Channel 4
        uint16_t toggle_val = decode_channel(frame[2], frame[3]);

        float yaw = lin_map(yaw_val, YAW_MIN_MAP, YAW_MAX_MAP);

        this->w.yaw = yaw;
        this->w.toggle = toggle_val;
        
        this->w.lastUpdate = xTaskGetTickCount();
    }
}

void Drone::parseUartBuffer(uint8_t* uart_buffer, uint32_t& uart_buffer_len) {
    int i = 0;

    if (uart_buffer_len < FRAME_SIZE) {
        return;
    }

    while (i <= uart_buffer_len - FRAME_SIZE) {
        if (uart_buffer[i] == 0x00 && uart_buffer[i+1] == 0x00 &&
            uart_buffer[i + FRAME_SIZE - 2] == 0xFF &&
            uart_buffer[i + FRAME_SIZE - 1] == 0xFF) {

            processFrame(&uart_buffer[i]);
            i += FRAME_SIZE;
            continue;
        }
        i++;
    }

    if (i < uart_buffer_len) {
        memmove(uart_buffer, &uart_buffer[i], uart_buffer_len - i);
        uart_buffer_len -= i;
    } else {
        uart_buffer_len = 0;
    }
}

void Drone::remoteControlReceiver() {
    uint8_t read_buf[128];
    uint8_t uart_buffer[RX_BUF_SIZE];
    uint32_t uart_buffer_len = 0;

    while (1) {
        int len = uart_read_bytes(UART_NUM, read_buf, sizeof(read_buf), pdMS_TO_TICKS(TIMEOUT_UART));
        if (len > 0) {
            if (uart_buffer_len + len > RX_BUF_SIZE) {
                uart_buffer_len = 0;
                ESP_LOGW("RECV", "UART buffer overflow, clearing buffer!\n");
            }
            
            memcpy(&uart_buffer[uart_buffer_len], read_buf, len);
            uart_buffer_len += len;
            
            parseUartBuffer(uart_buffer, uart_buffer_len);
        }
    }
}
void Drone::updatePosition(float x, float y, float z) {
    OrientationData orientation = this->orientation();

    const float offset_z_body = 0.11f; 

    float cp = std::cos(orientation.roll);
    float sp = std::sin(orientation.roll);
    float ct = std::cos(orientation.pitch);
    float st = std::sin(orientation.pitch);
    float cs = std::cos(orientation.yaw);
    float ss = std::sin(orientation.yaw);

    float off_x = offset_z_body * (cp * st * cs + sp * ss);
    float off_y = offset_z_body * (cp * st * ss - sp * cs);
    float off_z = offset_z_body * (cp * ct);

    float x_cog = x - off_x;
    float y_cog = y - off_y;
    float z_cog = z - off_z;

    if (startPosition.lastUpdate == 0) {
        startPosition.x = x_cog;
        startPosition.y = y_cog;
        startPosition.z = z_cog;
        startPosition.lastUpdate = xTaskGetTickCount();
    } else {
        position.x = x_cog - startPosition.x;
        position.y = y_cog - startPosition.y;
        position.z = z_cog - startPosition.z;
        position.lastUpdate = xTaskGetTickCount();
    }
}

PositionData& Drone::getPosition() {
    return position;
}
