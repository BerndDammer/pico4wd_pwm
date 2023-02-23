#include <stdbool.h>
#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#include "motor.h"

#define MOT1H 17
#define MOT1L 16
#define OFF_CHANNEL 15

#define FPWM 20000

typedef struct
{
    uint slice;
    int pinchana;
    int pinchanb;
    int is_inv;
    pwm_config pc;

} s_cs_mot;

void motor_init2(s_cs_mot *s)
{
    // Tell GPIO they are allocated to the PWM
    gpio_init(s->pinchana);
    gpio_init(s->pinchanb);
    gpio_set_function(s->pinchana, GPIO_FUNC_PWM);
    gpio_set_function(s->pinchanb, GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to GPIO
    //cs_mot1.slice = pwm_gpio_to_slice_num(MOT1H);

    s->pc = pwm_get_default_config();
    pwm_config_set_clkdiv_mode(&s->pc, PWM_DIV_FREE_RUNNING);

    //int div;
    double d;
    {
        d = (double) clock_get_hz(clk_sys) / (double) FPWM;
        d /= (double) DRIVE_MAX;
        //d *= 16.0;
        //div = (int)d;
        //printf("---- d %lf    div %li  div/16 %li\n", d, div, div/16);
        printf("---- d %f", d);
    }
    pwm_config_set_clkdiv(&s->pc, d);

    //s->pc.div = div;
    s->pc.top = DRIVE_MAX - 1;

    pwm_init(s->slice, &s->pc, false);

    pwm_set_chan_level(s->slice, PWM_CHAN_A, OFF_CHANNEL);
    pwm_set_chan_level(s->slice, PWM_CHAN_B, OFF_CHANNEL);

    pwm_set_enabled(s->slice, true);
}

s_cs_mot cs_mot1 =
{ 0, 17, 16,
true,
{

} };

void motor_init()
{
    motor_init2(&cs_mot1);
}

void motor_set(int pwm_val)
{
    if (pwm_val > 0)
    {
        pwm_set_chan_level(cs_mot1.slice, PWM_CHAN_A, DRIVE_MAX - pwm_val);
        pwm_set_chan_level(cs_mot1.slice, PWM_CHAN_B, DRIVE_MAX);
    }
    else
    {
        pwm_set_chan_level(cs_mot1.slice, PWM_CHAN_A, DRIVE_MAX);
        pwm_set_chan_level(cs_mot1.slice, PWM_CHAN_B, DRIVE_MAX + pwm_val);
    }
}
