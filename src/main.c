#include "timer.h"

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/watchdog.h"
#include "hardware/clocks.h"




int main()
{
    stdio_init_all();

    timer_init();


    puts("Hello, world!");

    return 0;
}
