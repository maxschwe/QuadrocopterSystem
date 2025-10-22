#include "esc_timer.h"

#include <driver/ledc.h>


EscTimer::EscTimer(ledc_timer_t timer_num)
    : timer_num(timer_num) {

    ledc_timer_config_t timer_conf = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .duty_resolution = ESC_PWM_RESOLUTION,
        .timer_num = this->timer_num,
        .freq_hz = ESC_PWM_FREQ_HZ,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&timer_conf);
}

ledc_timer_t EscTimer::getTimerNum() {
    return timer_num;
}
