/*
 * LED.c
 * Author: Adrian
 */

/*define the quarz frequency*/
#define F_CPU 12000000UL

/*include the std header files*/
#include <avr/io.h>
#include <util/delay.h>

/*blink every LED separately 5 times, then change the speed of the blinking*/
int main(void)
{
    /*set the direction of the pins*/
    DDRB = 0xFF;
    DDRC = 0xFF;
    DDRD = 0xFF;
    
    /*set the pins to 0*/
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    
    /*loop forever*/
    while(1)
    {
        /*blink every LED separately 5 times*/
        for(int i = 0; i < 5; i++)
        {
            PORTB = 0xFF;
            PORTC = 0xFF;
            PORTD = 0xFF;
            _delay_ms(1000);
            PORTB = 0x00;
            PORTC = 0x00;
            PORTD = 0x00;
            _delay_ms(1000);
        }
        
        /*change the speed of the blinking*/
        for(int i = 0; i < 5; i++)
        {
            PORTB = 0xFF;
            PORTC = 0xFF;
            PORTD = 0xFF;
            _delay_ms(500);
            PORTB = 0x00;
            PORTC = 0x00;
            PORTD = 0x00;
            _delay_ms(500);
        }
    }
}