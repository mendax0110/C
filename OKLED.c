/*include the librarys*/
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

#include "wiringPi.h"
#include "softPWM.h"

/*the OK/Act LED is connectedto BCM_GPIO pin 16.
 *now define the led and the pin.
 */
#define OK_LED  16

/*main part of the program.
 *so set everything up for the connection etc.
 */
int main()
{
    int fd, i;

    wiringPiSetupGpio();

    /*change the trigger on the OK/Act LED to "none"*/
    if((fd = open("/sys/class/leds/led0/trigger", O_RDWR)) < 0)
    {
        fprintf(stderr, "Unable to change LED trigger: %s\n", sterror (errno));
        return 1;
    }
    write(fd, "none\n", 5);
    close(fd);

    softPwmCreate(OK_LED, 0, 100);

    for(;;)
    {
        for(i = 0; i <= 100; ++i)
        {
            softPwmWrite(OK_LED, i);
            delay(10);
        }
        delay(50);

        for(i = 100; i >= 0; --i)
        {
            softPwmWrite(OK_LED, i);
            delay(10);
        }
        delay(10);
    }

    return 0;
}
