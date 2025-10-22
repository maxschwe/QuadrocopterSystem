#pragma once

#include <driver/ledc.h>

class Rotor {
public:
    Rotor(gpio_num_t pin, ledc_channel_t channel, EscTimer& timer);

    void setThrottle(float throttle_percent);

private:
    gpio_num_t pin;
    ledc_channel_t channel;
};
