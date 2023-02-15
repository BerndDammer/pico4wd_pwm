#include "timer.h"

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/watchdog.h"
#include "hardware/clocks.h"

int64_t alarm_callback(alarm_id_t id, void *user_data) {
    // Put your timeout handler code in here
    return 0;
}



int main()
{
    stdio_init_all();

    timer_init();


    puts("Hello, world!");

    return 0;
}
