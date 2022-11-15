/*
 * XNOR.c
 * Author: Adrian
 */

 /*define the quarz frequency*/
#define F_CPU 12000000UL

/*include the header files*/
#include <avr/io.h>
#include <util/delay.h>

/*inverter  in c ATMEGA16*/
int main(void)
{
    /*set the port as output*/
    DDRB = 0xFF;
    /*set the port as input*/
    DDRC = 0x00;
    /*set the port as pull up*/
    PORTC = 0xFF;
    while (1) 
    {
        /*read the input*/
        if(PINC & (1<<PC0))
        {
            /*set the output*/
            PORTB = 0xFF;
        }
        else
        {
            /*clear the output*/
            PORTB = 0x00;
        }
    }
}

