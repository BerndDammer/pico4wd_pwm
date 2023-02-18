#include "loop.h"
#include "blinker.h"
#include "motor.h"

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/watchdog.h"
#include "hardware/clocks.h"




void loop()
{
    volatile int c; // make visible in debugger; avoid optimize out
    int counter = 0;

    motor_set(20);

    for(;;)
    {
        c = getchar_timeout_us(1000000);
        if(c == PICO_ERROR_TIMEOUT)
        {
            printf("Hello, world! %i\n", counter);
            counter ++;
            motor_set(1000);
        }
        else
        {
            printf("Echo %c\n", c);
        }
        blinker_toggle();
    }
}
