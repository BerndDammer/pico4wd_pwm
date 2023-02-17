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
        c = getchar();
        if(c != EOF)
        {
            printf("Echo %c\n", c);
        }
        else
        {
            printf("Hello, world! %i\n", counter);
            sleep_ms(700);
            counter ++;
        }
    }
}
