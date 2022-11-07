/*include the libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "wiringPi.h"

/*main of the program*/
int main(void)
{
    int bright;

    /*print the message*/
    printf("Raspberry Pi Pico wiringPi PWM test program\n");

    if(wiringPiSetup() == -1)
    {
        printf("setup wiringPi failed!");
        return 1;
    }

    /*set the pin mode*/
    pinMode(1, PWM_OUTPUT);

    /*set the PWM range*/
    for(;;)
    {
        for(bright = 0; bright < 1024; bright++)
        {
            pwmWrite(1, bright);
            delay(1);
        }

        for(bright = 1023; bright >= 0; bright--)
        {
            pwmWrite(1, bright);
            delay(1);
        }
    }

    return 0;
}