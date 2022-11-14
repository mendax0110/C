/*
 * XNOR.c
 * Author: Adrian
 */

 /*define the quarz frequency*/
 #define F_CPU 12000000UL

/*include the header files*/
#include <avr/io.h>
#include <util/delay.h>

/*main xnor function ATMEGA16*/
int main(void)
{
   // set all ATMEGA1 pins
    DDRA = 0xFF;
    DDRB = 0xFF;
    DDRC = 0xFF;
    DDRD = 0xFF;

    // set all ATMEGA1 ports
    PORTA = 0xFF;
    PORTB = 0xFF;
    PORTC = 0xFF;
    PORTD = 0xFF;

    // XNOR function
    while(1)
    {
        PORTA = ~PORTA;
        PORTB = ~PORTB;
        PORTC = ~PORTC;
        PORTD = ~PORTD;
        _delay_ms(1000);
    }
    
}