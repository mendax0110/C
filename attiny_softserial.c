/*include the librarys*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <utils/delay.h>

/*define the sw-pin in softuart.h*/
#include "softuart.h"

#define PRINT_NL    softuart_putchar('\n')

/*define function to write ant integer to serial out*/
#define PRINT_INT_BUFSIZE   16

void printInt(int32_t i)
{
    char buf[PRINT_INT_BUFSIZE];
    int8_t sign = 1;
    int8_t len  = 0;

    /*look for the sign*/
    if(i < 0)
    {
        sign = -1;
        i    = -i;
    }

    /*fill buffer with digits(in reverse order)*/
    do
    {
        buf[len++] = 48 + i % 10; /*ASCII digits start at 48*/
    }
    while((i /= 10) > 0 && len < PRINT_INT_BUFSIZE);

    /*dont forget to add the sign*/
    if(sign < 0)
    {
        buf[len] = '-';
    }
    else
    {
        len--;
    }

    /*reverse output to the buffer*/
    do
    {
        softuart_putchar(buf[len--]);
    }
    while(len >= 0);
}

/*program entry point*/
int main(void)
{
    /*DDRB for the UART TX will be set in the softuart_init() functions!
     *we need to init softuart.
     */
    softuart_init();
    softuart_turn_rx_off(); /*cuz we dont receive serial data*/

    sei();

    /*main loop*/
    int8_t i = -128;
    int8_t d = 1;

    for(;;)
    {
        softuart_putchar('i');
        softuart_putchar('=');
        printInt(i);
        PRINT_NL;

        if(i == 128) d = -1; /*count down*/
        if(i == -128) d = 1; /*count up*/

        i += d;

        /*make a small delay*/
        _delay_ms(20);
    }

    return 0; /*never reached*/
}
