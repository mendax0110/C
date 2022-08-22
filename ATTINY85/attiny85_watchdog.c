/*include the library*/
#include <avr/interrupt.h>
#include <avr/sleep.h>

/*define the LED pin*/
#define LED PB0

/*setup the ISR*/
ISR(WDT_vect)
{
    /*toggle port B output 0 output state*/
    PORTB ^= _BV(LED);
}

/*main part of the program*/
int main(void)
{
    /*set port B output 0 as output*/
    DDRB = _BV(LED);

    /*perscale timer to 4 seconds*/
    WDTCR |= (1 << WDP2) | (1 << WDP0);

    /*enable the watchdog timer interrupts*/
    WDTCR |= (1 << WDTIE);

    /*enable the global interrupts*/
    sei();

    /*use the power down sleep mode*/
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);

    for(;;)
    {
        sleep_mode();   /*deep sleep, waiting for the interrupt*/
    }
}
