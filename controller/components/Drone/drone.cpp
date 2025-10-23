#include "drone.h"

#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "MPU6050.h"
#include "MPU6050_6Axis_MotionApps20.h"

#include "rotor.h"
#include "esc_timer.h"


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
    gpio_num_t rotor4_pin, ledc_channel_t rotor4_channel) : 
            esc_timer(timer_num),
            rotor1(rotor1_pin, rotor1_channel, this->esc_timer),
            rotor2(rotor2_pin, rotor2_channel, this->esc_timer),
            rotor3(rotor3_pin, rotor3_channel, this->esc_timer),
            rotor4(rotor4_pin, rotor4_channel, this->esc_timer)
{
    initI2C();

    this->mpu = MPU6050();
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
}

void Drone::print_ypr() {
    Quaternion q;           // [w, x, y, z]         quaternion container
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
    printf("YAW: %3.1f, ", ypr[0] * 180/M_PI);
    printf("PITCH: %3.1f, ", ypr[1] * 180/M_PI);
    printf("ROLL: %3.1f \n", ypr[2] * 180/M_PI);
}

VectorFloat Drone::ypr() {
    Quaternion q;           // [w, x, y, z]         quaternion container
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
    // printf("YAW: %3.1f, ", ypr[0] * 180/M_PI);
    // printf("PITCH: %3.1f, ", ypr[1] * 180/M_PI);
    // printf("ROLL: %3.1f \n", ypr[2] * 180/M_PI);

    return VectorFloat(ypr[2]* 180/M_PI, ypr[1] * 180/M_PI, ypr[0] * 180/M_PI);
}
