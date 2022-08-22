/*include the needed librarys*/
#include <avr/io.h>
#include <util/delay.h>

/*the frequency of the cpu is to be defined in the command line.
 *led is on pin 2, PB3
 */
#define LED         PB3
#define DELAY_MS    500

/*main part of the program*/
int main()
{
    uint8_t high = 0;
    uint16_t ms  = 0;

    /*setup LED pin for output in port B direction register*/
    DDRB |= (1 << LED);

    /*set LED pin LOW*/
    PORTB &= ~(1 << LED);

    while(1)
    {
        high =! high;

        if(high)
        {
            /*set LED pin HIGH*/
            PORTB |= (1 << LED);
        }
        else
        {
            /*set LED pin LOW*/
            PORTB &= ~(1 << LED);
        }

        /*set the delay to 500 ms*/
        for(ms = DELAY_MS; ms > 0; ms -= 10)
        {
            _delay_ms(10);
        }
    }

    return 0;
}