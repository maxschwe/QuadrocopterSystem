#include <driver/gpio.h>
#include <driver/i2c.h>

#include <esp_err.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>

// #include "driver/uart.h"
#include "MPU6050.h"
#include "MPU6050_6Axis_MotionApps20.h"

// Onboard LED


// ESC timer
const int ESC_PWM_FREQ_HZ = 50;
const ledc_timer_bit_t ESC_PWM_RESOLUTION = LEDC_TIMER_16_BIT;
const ledc_timer_t ESC_TIMER = LEDC_TIMER_0;

// Rotor configurations
const gpio_num_t ROTOR_1_PIN = GPIO_NUM_15;
const ledc_channel_t ROTOR_1 = LEDC_CHANNEL_0;

volatile bool run_tasks = true;

#define PIN_SDA 21
#define PIN_CLK 22

Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
uint16_t packetSize = 42;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU

void task_initI2C(void *ignore) {
	i2c_config_t conf;
	conf.mode = I2C_MODE_MASTER;
	conf.sda_io_num = (gpio_num_t)PIN_SDA;
	conf.scl_io_num = (gpio_num_t)PIN_CLK;
	conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
	conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
	conf.master.clk_speed = 400000;
	ESP_ERROR_CHECK(i2c_param_config(I2C_NUM_0, &conf));
	ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0));
	vTaskDelete(NULL);
}

void task_display(void*){
	MPU6050 mpu = MPU6050();
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

	while(1){
	    mpuIntStatus = mpu.getIntStatus();
		// get current FIFO count
		fifoCount = mpu.getFIFOCount();

	    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
	        // reset so we can continue cleanly
	        mpu.resetFIFO();

	    // otherwise, check for DMP data ready interrupt frequently)
	    } else if (mpuIntStatus & 0x02) {
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

	    //Best result is to match with DMP refresh rate
	    // Its last value in components/MPU6050/MPU6050_6Axis_MotionApps20.h file line 310
	    // Now its 0x13, which means DMP is refreshed with 10Hz rate
		// vTaskDelay(5/portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);
}

// void rotor_init(int pin, ledc_channel_t channel, ledc_timer_t timer)
// {
//     // Configure channel
//     ledc_channel_config_t ledc_channel = {
//         .gpio_num = pin,
//         .speed_mode = LEDC_HIGH_SPEED_MODE,
//         .channel = channel,
//         .intr_type = LEDC_INTR_DISABLE,
//         .timer_sel = timer,
//         .duty = 0};
//     ledc_channel_config(&ledc_channel);
// }

// void set_throttle(float throttle, ledc_channel_t channel)
// {
//     float pulse_width = 1.0 / 20.0 + (throttle / 100.0) * (1.0 / 20.0); // Map 0-100% to 1-2ms pulse
//     uint32_t duty = (uint32_t)(pulse_width * ((1 << 16) - 1));
//     ledc_set_duty(LEDC_HIGH_SPEED_MODE, channel, duty);
//     ledc_update_duty(LEDC_HIGH_SPEED_MODE, channel);
// }

// void rotors_init()
// {
//     ledc_timer_config_t ledc_timer = {
//         .speed_mode = LEDC_HIGH_SPEED_MODE,
//         .timer_num = ESC_TIMER,
//         .duty_resolution = ESC_PWM_RESOLUTION,
//         .freq_hz = ESC_PWM_FREQ_HZ,
//         .clk_cfg = LEDC_AUTO_CLK};
//     ledc_timer_config(&ledc_timer);

//     rotor_init(ROTOR_1_PIN, ROTOR_1, ESC_TIMER);
//     set_throttle(0, ROTOR_1);

//     vTaskDelay(pdMS_TO_TICKS(3000));
// }

// void scale_init()
// {
//     uart_config_t uart_config = {
//         .baud_rate = 9600,
//         .data_bits = UART_DATA_8_BITS,
//         .parity = UART_PARITY_DISABLE,
//         .stop_bits = UART_STOP_BITS_1,
//         .flow_ctrl = UART_HW_FLOWCTRL_DISABLE};
//     uart_param_config(UART_NUM_2, &uart_config);
//     uart_set_pin(UART_NUM_2, 17, 16, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
//     uart_driver_install(UART_NUM_2, 1024, 0, 0, NULL, 0);
// }

// float measure_weight_average()
// {
//     const int samples = 10;
//     float total_weight = 0.0;

//     const int RESPONSE_BUFFER_SIZE = 18;
//     char data[RESPONSE_BUFFER_SIZE];

//     for (int i = 0; i < samples; i++)
//     {
//         uart_write_bytes(UART_NUM_2, "w", 1);

//         int len = uart_read_bytes(UART_NUM_2, data, RESPONSE_BUFFER_SIZE, 2000 / portTICK_PERIOD_MS);

//         if (len == RESPONSE_BUFFER_SIZE)
//         {
//             data[12] = '\0';
//             float weight = atoi(&data[2]);
//             total_weight += weight;
//         }
//         else
//         {
//             ESP_LOGE("SCALE", "Failed to read weight data, Len: %d", len);
//         }
//     }

//     float average_weight = total_weight / samples;
//     ESP_LOGI("SCALE", "Average Weight: %.2f", average_weight);

//     return average_weight;
// }

// void test_motor_ramp(void *pvParameters)
// {
//     scale_init();
//     rotors_init();

//     int lowest_throttle = 10;
//     int highest_throttle = 100;
//     int step_size = 2;

//     int measurement_count = (highest_throttle - lowest_throttle) / step_size + 1;

//     float weights[measurement_count];

//     // Ramp up motor
//     for (int duty = lowest_throttle, i = 0; duty <= highest_throttle && run_tasks; duty += step_size, i++)
//     {
//         set_throttle(duty, ROTOR_1);
//         ESP_LOGI("ESC", "Throttle: %d", duty);
//         vTaskDelay(pdMS_TO_TICKS(1000));
//         weights[i] = measure_weight_average();
//     }

//     set_throttle(0, ROTOR_1);

//     printf("WEIGHT_DATA: [ %.2f", weights[0]);
//     for (int i = 1; i < measurement_count; i++)
//     {
//         printf(", %.2f", weights[i]);
//     }
//     printf(" ]\n");

//     vTaskDelete(NULL);
// }



// void uart_monitor_task(void *pvParameter)
// {
//     // Initialize UART0
//     uart_config_t uart_config = {
//         .baud_rate = 115200,
//         .data_bits = UART_DATA_8_BITS,
//         .parity = UART_PARITY_DISABLE,
//         .stop_bits = UART_STOP_BITS_1,
//         .flow_ctrl = UART_HW_FLOWCTRL_DISABLE};
//     uart_param_config(UART_NUM_0, &uart_config);
//     uart_driver_install(UART_NUM_0, 1024, 0, 0, NULL, 0);

//     uint8_t data[1024];
//     while (1)
//     {
//         int len = uart_read_bytes(UART_NUM_0, data, 1024, 20 / portTICK_PERIOD_MS);
//         if (len > 0)
//         {
//             for (int i = 0; i < len; i++)
//             {
//                 if (data[i] == 0x03)
//                 { // ASCII for Ctrl+C
//                     printf("Ctrl+C received! Stopping all tasks...\n");
//                     run_tasks = false;
//                 }
//             }
//         }
//         vTaskDelay(pdMS_TO_TICKS(10));
//     }
// }


extern "C" void app_main(void)
{
    // xTaskCreate(test_motor_ramp, "Ramp up Task", 4096, NULL, 5, NULL);
    // xTaskCreate(uart_monitor_task, "UART Monitor", 2048, NULL, 10, NULL);
    xTaskCreate(&task_initI2C, "mpu_task", 2048, NULL, 5, NULL);
    vTaskDelay(500/portTICK_PERIOD_MS);
    xTaskCreate(&task_display, "disp_task", 8192, NULL, 5, NULL);
}
