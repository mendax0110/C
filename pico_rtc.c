/*SPDX-license-Identifier: BSD-3-Clause*/
#include <stdio.h>
#include "hardware/rtc.h"
#include "pico/stdlib.h"
#include "pico/util/datetime.h"

/*tag::hello_rtc_main()*/
int main()
{
    stdio_init_all();
    printf("Send a package to RTC!\n");

    char datetime_buf[256];
    char *datetime_str = &datetime_buf[0];

    /*start on a friday*/
    datetime_t t = {
        .year  = 2021,
        .month = 12,
        .day   = 14,
        .dotw  = 2,
        .hour  = 12,
        .min   = 23,
        .sec   = 00 
    };

    /*start the rtc*/
    rtc_init();
    rtc_set_datetime(&t);

    /*print the time*/
    while(true)
    {
        rtc_get_datetime(&t);
        datetime_to_str(datetime_str, sizeof(datetime_buf), &t);
        printf("\r%s          ", datetime_str);
        sleep_ms(100);
    }

    return 0;
}
/*end::hello_rtc_main()*/
