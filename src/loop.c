#include "loop.h"
#include "blinker.h"
#include "motor.h"

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/watchdog.h"
#include "hardware/clocks.h"

#define CONSOLE_TIMEOUT 1000000
#define STEP_STEP (DRIVE_MAX / 10)

void menu(void)
{
    printf("------------------------------------\n");
    printf("1 Front Left \n");
    printf("2 Front right \n");
    printf("3 Rear Left \n");
    printf("4 Rear right \n");
    printf("u up \n");
    printf("d down\n");
    printf("0 or (space) shutdown all\n");
    printf("press key to select\n");
    printf("------------------------------------\n");
}

int step_value = DRIVE_OFF;

void shutdown(void)
{
    for (int i = FRONT_LEFT; i <= REAR_RIGHT; i++)
    {
        motor_set(i, DRIVE_OFF);
    }
    step_value = DRIVE_OFF;
}


void loop(void)
{
    printf("------------------------------------\n");
    printf("clock_get_hz(clk_sys) %u\n", clock_get_hz(clk_sys));
    printf("------------------------------------\n");

    volatile int c; // make visible in debugger; avoid optimize out
    int counter = 0;
    enum WHEEL wheel = FRONT_LEFT;

    shutdown();

    menu();

    for (;;)
    {
        c = getchar_timeout_us(CONSOLE_TIMEOUT);
        blinker_toggle();

        if (c == PICO_ERROR_TIMEOUT)
        {
            printf("Loop Counter %i\n", counter);
            counter++;
        }
        else
        {
            switch (c)
            {
            case '1':
                wheel = FRONT_LEFT;
                shutdown();
                puts("Selected wheel: FRONT_LEFT");
                break;
            case '2':
                wheel = FRONT_RIGHT;
                shutdown();
                puts("Selected wheel: FRONT_RIGHT");
                break;
            case '3':
                wheel = REAR_LEFT;
                shutdown();
                puts("Selected wheel: REAR_LEFT");
                break;
            case '4':
                wheel = REAR_RIGHT;
                shutdown();
                puts("Selected wheel: REAR_RIGHT");
                break;
            case 'u':
                step_value += STEP_STEP;
                if (step_value > DRIVE_MAX)
                    step_value = DRIVE_MAX;
                motor_set(wheel, step_value);
                printf("New step value %i\n", step_value);
                break;
            case 'd':
                step_value -= STEP_STEP;
                if (step_value < DRIVE_MIN)
                    step_value = DRIVE_MIN;
                motor_set(wheel, step_value);
                printf("New step value %i\n", step_value);
                break;
            case ' ':
            case '0':
                shutdown();
                printf("New step value %i\n", step_value);
                break;
            default:
                menu();
                break;
            }
        }
    }
}
