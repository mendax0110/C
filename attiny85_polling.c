/*include the librarys*/
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdbool.h>

/*define the LED, SWITCH, RECEIVE*/
#define LED             PB0
#define SWITCH_EMPTY    PINB3
#define SWITCH_RECEIVE  PINB4

/*set the bool and int*/
bool    gotmail = false;
int     counter = 0;

/*setup the ISR*/
ISR(WDT_vect)
{
    if((PINB & _BV(SWITCH_RECEIVE)) == 0)
    {
        gotmail = true;
    }
    else if((PINB & _BV(SWITCH_EMPTY)) == 0)
    {
        gotmail = false;
    }
    if(gotmail)
    {
        if(counter == 3)
        {
            PORTB |= _BV(LED);
            _delay_ms(200);
            PORTB &= ~_BV(LED);
            counter = 0;
        }
        else
        {
            counter++;
        }
    }
}

/*main part of the program*/
int main(void)
{
    DDRB |= _BV(LED);
    WDTCR |= (1 << WDP2) | (1 << WDP0);
    WDTCR |= (1 << WDTIE);
    sei();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);

    for(;;)
    {
        sleep_mode();
    }
}
