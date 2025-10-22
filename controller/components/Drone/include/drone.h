#pragma once

#include <driver/ledc.h>
#include <driver/gpio.h>

#include "rotor.h"
#include "esc_timer.h"

class Drone {
    public:
        Drone(ledc_timer_t timer_num, 
              gpio_num_t rotor1_pin, ledc_channel_t rotor1_channel, 
              gpio_num_t rotor2_pin, ledc_channel_t rotor2_channel,
              gpio_num_t rotor3_pin, ledc_channel_t rotor3_channel,
              gpio_num_t rotor4_pin, ledc_channel_t rotor4_channel);
    private:
        EscTimer esc_timer;
        Rotor rotor1;
        Rotor rotor2;
        Rotor rotor3;
        Rotor rotor4;
};
