#include "drone.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "rotor.h"
#include "esc_timer.h"

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
    rotor1.setThrottle(0.0f);
    rotor2.setThrottle(0.0f);
    rotor3.setThrottle(0.0f);
    rotor4.setThrottle(0.0f);

    vTaskDelay(pdMS_TO_TICKS(3000));
}
