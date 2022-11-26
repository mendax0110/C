/*
 * Taster.c
 *
 * Created: 12.11.2022 18:53:52
 *  Author: Adrian
 */ 
#define F_CPU 12000000UL    // 12Mhz Systemtakt 
#include  <avr/io.h>        // AVR Libc
#include  <util/delay.h>    // AVR Libc

#define TASTER PA0       // Taster an PA0
#define T_PRELL 20       // 20ms Prellzeit

// mit taster prellen alle leds durchschalten
int main(void)
{
    // I/O Konfiguration
    DDRA  = 0x00;           // Port A als Eingang
    PORTA = 0x0F;           // Pullup Widerstände aktivieren
    DDRC  = 0xFF;           // Port C als Ausgang
    PORTC = 0x01;           // LEDs ausschalten

    // arbeiten in einer Endlosschleife
    while(1)
    {
        if(!(PINA & (1<<TASTER)))   // wenn Taster gedrückt
        {
            _delay_ms(T_PRELL);     // Prellzeit warten
            if(!(PINA & (1<<TASTER)))   // wenn Taster immer noch gedrückt
            {
                PORTC = PORTC<<1;   // nächste LED einschalten
                if(PORTC == 0)      // wenn alle LEDs an
                    PORTC = 0x01;   // erste LED einschalten
            }
            while(!(PINA & (1<<TASTER)));   // warten bis Taster losgelassen
        }
    }
}
