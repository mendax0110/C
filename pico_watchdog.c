/*include all the needed librarys*/
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/watchdog.h"

/*now the main part of the code*/
int main()
{
    stdio_init_all();

    /*rebooted by watchdog*/
    if(watchdog_caused_reboot())
    {
        printf("Rebooted by Watchdog!\n");
        return 0;
    }
    else
    {
        printf("Clean boot\n");
    }

    /*enable the watchdog, requiring the watchdog to be updated every 100ms,
     *or the chip will reboot.
     *second arg is paused on debug which means the watchdig will pause when,
     *stepping through code.
     */
    watchdog_enable(100, 1);

    for(uint i = 0; i < 5; i++)
    {
        printf("Updating Watchdog %d\n", i);
        watchdog_update();
    }

    /*wait in an inifinite loop and don't update the watchdog so it reboots us*/
    printf("Waiting to be rebooted by watchdog\n");
    while(1);
}
