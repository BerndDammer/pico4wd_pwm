#include <stdbool.h>

#include "pico/stdlib.h"
#include "hardware/pwm.h"

#include "motor.h"

#define MOT1H 17
#define MOT1L 16
#define WRAP 3000

typedef struct
{
    uint slice;
    int moth;
    int motl;
    int is_inv;
    pwm_config pc;

} s_cs_mot;

void motor_init2(s_cs_mot *s)
{
    // Tell GPIO they are allocated to the PWM
    gpio_set_function(s->moth, GPIO_FUNC_PWM);
    gpio_set_function(s->motl, GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to GPIO
    //cs_mot1.slice = pwm_gpio_to_slice_num(MOT1H);

    s->pc = pwm_get_default_config();
    pwm_config_set_clkdiv_mode(&s->pc, PWM_DIV_FREE_RUNNING);
    pwm_config_set_clkdiv(&s->pc, WRAP);

    s->pc.div = 0XFFFFFF;
    s->pc.top = WRAP;

    pwm_init(s->slice, &s->pc, false);

    pwm_set_chan_level(s->slice, PWM_CHAN_A, 0);
    pwm_set_chan_level(s->slice, PWM_CHAN_B, 0);

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
        pwm_set_chan_level(cs_mot1.slice, PWM_CHAN_A, pwm_val);
        pwm_set_chan_level(cs_mot1.slice, PWM_CHAN_B, 0);
    }
    else
    {
        pwm_set_chan_level(cs_mot1.slice, PWM_CHAN_A, 0);
        pwm_set_chan_level(cs_mot1.slice, PWM_CHAN_B, -pwm_val);
    }
}
