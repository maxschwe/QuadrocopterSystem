#pragma once

#include <driver/ledc.h>

#define ESC_PWM_RESOLUTION LEDC_TIMER_16_BIT
#define ESC_PWM_FREQ_HZ 50

class EscTimer {
public:
    EscTimer(ledc_timer_t timer_num);
    ledc_timer_t getTimerNum();

private: 
    ledc_timer_t timer_num;
};