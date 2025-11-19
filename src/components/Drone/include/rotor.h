#pragma once

#include <driver/ledc.h>

#include "esc_timer.h"

class Rotor {
public:
    Rotor(gpio_num_t pin, ledc_channel_t channel, EscTimer& timer);

    void setThrottle(float throttle_percent);
    void init();

private:
    gpio_num_t pin;
    ledc_channel_t channel;
};
