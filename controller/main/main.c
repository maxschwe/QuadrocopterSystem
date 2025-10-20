#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/uart.h"

// Onboard LED
#define BLINK_GPIO 2

// ESC timer
#define ESC_PWM_FREQ_HZ 50
#define ESC_PWM_RESOLUTION LEDC_TIMER_16_BIT
#define ESC_TIMER LEDC_TIMER_0

// Rotor configurations
#define ROTOR_1_PIN 15
#define ROTOR_1 LEDC_CHANNEL_0

volatile bool run_tasks = true;

void init_rotor(int pin, ledc_channel_t channel, ledc_timer_t timer)
{
    // Configure channel
    ledc_channel_config_t ledc_channel = {
        .gpio_num       = pin,
        .speed_mode     = LEDC_HIGH_SPEED_MODE,
        .channel        = channel,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = timer,
        .duty           = 0
    };
    ledc_channel_config(&ledc_channel);
}

void set_throttle(float throttle, ledc_channel_t channel)
{
    float pulse_width = 1.0 / 20.0 + (throttle / 100.0) * (1.0 / 20.0); // Map 0-100% to 1-2ms pulse
    uint32_t duty = (uint32_t)(pulse_width * ((1 << 16) - 1));
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, channel, duty);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, channel);
}

void init_rotors()
{
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_HIGH_SPEED_MODE,
        .timer_num        = ESC_TIMER,
        .duty_resolution  = ESC_PWM_RESOLUTION,
        .freq_hz          = ESC_PWM_FREQ_HZ,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    init_rotor(ROTOR_1_PIN, ROTOR_1, ESC_TIMER);
    set_throttle(0, ROTOR_1);

    vTaskDelay(pdMS_TO_TICKS(3000));
}

void init_scale() {
    uart_config_t uart_config = {
        .baud_rate = 19200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM_2, &uart_config);
    uart_driver_install(UART_NUM_2, 1024, 0, 0, NULL, 0);
}

void measure_weight_average() {
    const int samples = 10;
    float total_weight = 0.0;

    const int RESPONSE_BUFFER_SIZE = 18;
    char data[RESPONSE_BUFFER_SIZE];

    for (int i = 0; i < samples; i++) {
        uart_write_bytes(UART_NUM_2, "w", 1);

        int len = uart_read_bytes(UART_NUM_2, data, RESPONSE_BUFFER_SIZE, 2000 / portTICK_PERIOD_MS);

        if (len == RESPONSE_BUFFER_SIZE) {
            data[12] = '\0';
            float weight = atoi(&data[2]);
            total_weight += weight;
        } else {
            ESP_LOGE("SCALE", "Failed to read weight data, Len: %d", len);
        }
    }

    float average_weight = total_weight / samples;
    ESP_LOGI("SCALE", "Average Weight: %.2f", average_weight);
}

void test_motor_ramp(void *pvParameters)
{   
    init_rotors();
    init_scale();

    // Ramp up motor
    for (int8_t duty = 30; duty <= 100 && run_tasks; duty += 2) {
        set_throttle(duty, ROTOR_1);
        ESP_LOGI("ESC", "Throttle: %d", duty);
        vTaskDelay(pdMS_TO_TICKS(20));
        measure_weight_average();
    }

    set_throttle(0, ROTOR_1);

    vTaskDelete(NULL);
}

void test_led(void *pvParameters)
{
    gpio_reset_pin(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    while (run_tasks) {
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}

void uart_monitor_task(void *pvParameter) {
    // Initialize UART0
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM_0, &uart_config);
    uart_driver_install(UART_NUM_0, 1024, 0, 0, NULL, 0);

    uint8_t data[1024];
    while(1) {
        int len = uart_read_bytes(UART_NUM_0, data, 1024, 20 / portTICK_PERIOD_MS);
        if(len > 0) {
            for(int i = 0; i < len; i++) {
                if(data[i] == 0x03) {  // ASCII for Ctrl+C
                    printf("Ctrl+C received! Stopping all tasks...\n");
                    run_tasks = false;
                }
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}


void app_main(void)
{
    xTaskCreate(test_led, "Blink Task", 2048, NULL, 5, NULL);
    xTaskCreate(test_motor_ramp, "Ramp up Task", 2048, NULL, 5, NULL);
    xTaskCreate(uart_monitor_task, "UART Monitor", 2048, NULL, 10, NULL);
}
