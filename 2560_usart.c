/*voltmeter which is based on an atmega16, sends the A2D conversion
 *results over RS232 to the connected PC.
 */
#ifdef  F_CPU
#define F_CPU       8000000
#endif

#define FOSC        8000000
#define BAUDRATE    9600
#define UBRR        (FOSC/(BAUDRATE << 4))-1

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

/*called when USART completes receiving data*/
ISR(USART_RX_vect)
{
    /*read UDR register to reset flag*/
    unsigned char data = UDR0;

    /*check for error*/
    if((UCSR0A && ((1 << FE0) | (1 << DOR0) | (1 << UPE0))) == 0)
    {
        /*no error occured*/
        if(data == 'r')
        {
            /*start ADC conversion*/
            ADCSRA = (1 << ADSC);
        }
    }
}

/*called when the data register accepts new data*/
ISR(USART_UDRE_vect)
{
    /*write ADC value*/
    UDR0 = ADCH;

    /*disable this interrupt*/
    UCSR0B &= ~(1 << UDRIE0);
}

/*called when the ADC completes a conversion*/
ISR(ADC_vect)
{
    static uint8_t i = 0;

    UCSR0B |= (1 << UDRIE0);

    i++;

    if(i < 6)
    {
        /*start a new conversion*/
        ADCSRA = (1 << ADSC);
    }
    else
    {
        i = 0;
    }
}

void usart_init(uint16_t ubrr_value)
{
    UBRR0 = ubrr_value;

    /*9600-8-E-1
     *that is the baudrate of 9600 bps
     *8 databits
     *even parity
     *1 stopbit
     */
    UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0); /*and enable the interrupts*/
    UCSR0c = (1 << UPM01) | (1 << UCSZ01) | (1 << UCSZ00);
}

void adc_init()
{
    /*setup the adc*/
    ADMUX = (1 << ADLAR);

    /*enable the adc unit and use a prescaler*/
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
}

int main()
{
    /*setup the usart*/
    usart_init(UBRR);

    /*setup adc*/
    adc_init();

    /*enable the interrupts*/
    sei();

    while(1)
    {
        /*nothing more to do here!*/
    }

    return 0;
}
