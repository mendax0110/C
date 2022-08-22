/*include the needed librarys*/
#include <avr/io.h>
#include <util/delay.h>

/*define the led and the pin*/
#define LED PB0

/*main part of the program*/
int main(void)
{
    /*set port b output as output*/
    DDRB |= _BV(LED);

    /*COM0A1 - COM0A0 (Set OC0A on compare match, clear OC0A at TOP, set fast PWM)*/
    TCCR0A |= (_BV(COM0A1) | _BV(COM0A0) | _BV(WGM01) | _BV(WGM00));

    /*initialize Output compare register A to 0*/
    OCR0A = 0;

    /*start timer at Fcpu / 256*/
    TCCR0B |= (1 << CS01);

    for(int i;;)
    {
        /*update the output compare register (PWM 0-100%)*/
        for(i = 0; i < 255; i++)
        {
            OCR0A = i;
            _delay_ms(5);
        }
        /*update output compare register (PWM 100%-0)*/
        for(i = 255; i > 0; i--)
        {
            OCR0A = i;
            _delay_ms(5);
        }
    }
}
