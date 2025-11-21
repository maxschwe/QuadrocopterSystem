#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/gpio.h>

const gpio_num_t BLINK_GPIO = GPIO_NUM_2;

static void onboard_led_test(void *pvParameters)
{
    while (1) {
        gpio_reset_pin(BLINK_GPIO);
        gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void start_onboard_led_test()
{
    xTaskCreate(onboard_led_test, "Blink Task", 2048, NULL, 5, NULL);
}
