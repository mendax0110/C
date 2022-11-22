/*define the quarz frequency*/
#define F_CPU 12000000UL

/*include the std header files*/
#include <avr/io.h>
#include <util/delay.h>

/*make a running light for 8 leds using 8 pins of portc*/
int main(void)
{
    /*set the direction of portc as output*/
    DDRC = 0xFF;
    /*set the value of portc as 0*/
    PORTC = 0x00;
    /*make a loop*/
    while(1)
    {
        /*make a loop for 8 leds*/
        for(int i=0; i<8; i++)
        {
            /*set the value of portc as 1*/
            PORTC = 0x01;
            /*shift the value of portc to the left*/
            PORTC = PORTC << i;
            /*delay for 1 second*/
            _delay_ms(1000);
        }
    }
    return 0;
}