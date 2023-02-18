#include "loop.h"
#include "blinker.h"
#include "motor.h"

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/watchdog.h"
#include "hardware/clocks.h"

#define CONSOLE_TIMEOUT 5000000
#define STEP_MAX 3000
#define STEP_STEP 300

void menu(void)
{
    printf("------------------------------------\n");
    printf("u up \n");
    printf("d down\n");
    printf("0 or (space) pwm 0\n");
    printf("press key to select\n");
    printf("------------------------------------\n");
}

void loop()
{
    volatile int c; // make visible in debugger; avoid optimize out
    int counter = 0;
    int step_value = 100;

    menu();
    motor_set(step_value);

    for (;;)
    {
        c = getchar_timeout_us(CONSOLE_TIMEOUT);
        if (c == PICO_ERROR_TIMEOUT)
        {
            printf("Loop Counter %i\n", counter);
            counter++;
        }
        else
        {
            switch (c)
            {
            case 'u':
                step_value += STEP_STEP;
                if (step_value > STEP_MAX)
                    step_value = STEP_MAX;
                motor_set(step_value);
                printf("New step value %i\n", step_value);
                break;
            case 'd':
                step_value -= STEP_STEP;
                if (step_value < -STEP_MAX)
                    step_value = -STEP_MAX;
                motor_set(step_value);
                printf("New step value %i\n", step_value);
                break;
            case ' ':
            case '0':
                step_value = 0;
                motor_set(step_value);
                printf("New step value %i\n", step_value);
                break;
            default:
                menu();
                break;
            }
        }
        blinker_toggle();
    }
}
