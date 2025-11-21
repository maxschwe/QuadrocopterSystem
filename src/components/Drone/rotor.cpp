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

void Rotor::init()
{
    setThrottle(0.0f);
    vTaskDelay(pdMS_TO_TICKS(3000));
}

void Rotor::setThrottle(float throttle_percent)
{
    // Map 0-100% throttle to 1-2ms pulse width
    float min_pulse_ms = 1.0f;
    float max_pulse_ms = 2.0f;
    const float pulse_range = max_pulse_ms - min_pulse_ms;
    const float period_ms = 1000.0f / ESC_PWM_FREQ_HZ;

    float pulse_ms = min_pulse_ms + (throttle_percent / 100.0f) * pulse_range;
    uint32_t max_duty = (1 << ESC_PWM_RESOLUTION) - 1;
    uint32_t duty = (uint32_t)((pulse_ms / period_ms) * max_duty);

    ledc_set_duty(LEDC_HIGH_SPEED_MODE, channel, duty);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, channel);
}
