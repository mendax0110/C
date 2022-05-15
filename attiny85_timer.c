/*include the librarys*/
#include <avr/interrupt.h>

/*define the LED PIN*/
#define LED PB0

/*setup the ISR*/
ISR(TIM0_OVF_vect)
{
    /*toggle port B pin 4 output state*/
    PORTB ^= _BV(LED);
}

/*main part of the program*/
int main(void)
{
    /*set port b output 0 as output*/
    DDRB = _BV(LED);

    /*prescaler timer to 1/1024th the clock rate*/
    TCCR0B |= _BV(CS02) | _BV(CS00);

    /*enable timer overflow interrupt*/
    TIMSK0 |= _BV(TOIE0);

    /*enable interrupts*/
    sei();

    /*loop forever*/
    while(1)
    {

    }
}
