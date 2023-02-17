#include "loop.h"

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/watchdog.h"
#include "hardware/clocks.h"




void loop()
{
    volatile int c;
    int counter = 0;
    for(;;)
    {
        c = getchar_timeout_us(700000);
        if(c == PICO_ERROR_TIMEOUT)
        {
            printf("Hello, world! %i\n", counter);
            //sleep_ms(700);
            counter ++;
        }
        else
        {
            printf("Echo %c\n", c);
        }
    }
}
