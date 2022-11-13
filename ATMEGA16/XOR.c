/*
 * XOR.c
 * Author: Adrian
 */

 /*define the quarz frequency*/
#define F_CPU 12000000UL

/*include the header files*/
#include <avr/io.h>
#include <util/delay.h>

/*main xor function*/
int main(void)
{
    /*XOR function with LED ATMEGA 16*/

    DDRC = 0xFF; //set PORTC as output
    PORTC = 0x00; //set PORTC as low

    while(1)
    {
        PORTC ^= 0xFF; //XOR PORTC
        _delay_ms(1000); //delay 1 second

        PORTC =~ PORTC; //invert PORTC
        _delay_ms(1000); //delay 1 second
    }
}