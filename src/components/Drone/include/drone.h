#pragma once

#include <driver/ledc.h>
#include <driver/gpio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "MPU6050.h"

#include "rotor.h"
#include "esc_timer.h"


struct ReferenceInputs {
	float roll;
	float pitch;
	float yaw;
	float throttle;

	uint16_t toggle;

	TickType_t lastUpdate;
};

struct OrientationData {
    float roll;
    float pitch;
    float yaw;

    TickType_t lastUpdate;
};

class Drone {
    public:
        Drone(ledc_timer_t timer_num, 
              gpio_num_t rotor1_pin, ledc_channel_t rotor1_channel, 
              gpio_num_t rotor2_pin, ledc_channel_t rotor2_channel,
              gpio_num_t rotor3_pin, ledc_channel_t rotor3_channel,
              gpio_num_t rotor4_pin, ledc_channel_t rotor4_channel,
              gpio_num_t mpu_interrupt_pin, bool remote_control_enabled);

        void setThrottles(float throttle1, float throttle2, float throttle3, float throttle4);
        OrientationData rpy();
        void printRpy();
        VectorFloat gyro();

        ReferenceInputs& getReferenceInputs();

    private:
        EscTimer esc_timer;
        Rotor rotor1;
        Rotor rotor2;
        Rotor rotor3;
        Rotor rotor4;
        MPU6050 mpu;

        TaskHandle_t mpuProcessingTaskHandle;
        QueueHandle_t mpuMailbox;

        ReferenceInputs w;

        bool initMpu(gpio_num_t mpu_interrupt_pin);

        static void IRAM_ATTR wrapperOnMpuInterrupt(void *drone);
        void IRAM_ATTR onMpuInterrupt();

        static void wrapperMPUInterruptProcessor(void *drone);
        void mpuInterruptProcessor();

        void initRotors();
        
        void startRemoteControlReceiver();
        static void wrapperRemoteControlReceiver(void *drone);
        void remoteControlReceiver();
        void processFrame(uint8_t* frame);
        void parseUartBuffer(uint8_t* uart_buffer, uint32_t& uart_buffer_len);
};
