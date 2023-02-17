#include "loop.h"

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/watchdog.h"
#include "hardware/clocks.h"




void loop()
{
    for(;;)
    {
        puts("Hello, world!");
        sleep_ms(700);

    }

}
