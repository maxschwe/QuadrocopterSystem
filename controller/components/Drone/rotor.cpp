#include "rotor.h"

#include <driver/ledc.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "esc_timer.h"

Rotor::Rotor(gpio_num_t pin, ledc_channel_t channel, EscTimer &timer)
    : pin(pin), channel(channel)
{
    // Configure channel
    ledc_channel_config_t ledc_channel = {};
    ledc_channel.gpio_num = pin;
    ledc_channel.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_channel.channel = channel;
    ledc_channel.intr_type = LEDC_INTR_DISABLE;
    ledc_channel.timer_sel = timer.getTimerNum();
    ledc_channel.duty = 0;
    ledc_channel_config(&ledc_channel);
}

void Rotor::setThrottle(float throttle_percent)
{
    // Map 0-100% throttle to 1-2ms pulse width
    float min_pulse_ms = 1.0;
    float max_pulse_ms = 2.0;
    float pulse_ms = min_pulse_ms + (throttle_percent / 100.0) * (max_pulse_ms - min_pulse_ms);

    // Convert pulse width to duty cycle
    uint32_t max_duty = (1 << ESC_PWM_RESOLUTION) - 1;
    uint32_t duty = (uint32_t)((pulse_ms / (1000.0 / ESC_PWM_FREQ_HZ)) * max_duty);

    ledc_set_duty(LEDC_HIGH_SPEED_MODE, channel, duty);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, channel);
}
