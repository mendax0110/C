/*define the CPU*/
#define F_CPU   16500000UL
/*include the needed libararys*/
#include <avr/io.h>
#include <util/delay.h>

/*macros who are indirectly used by other macros for amterl GCC-AVR*/
#define _SET(type,name,bit)         type ## name |= _BV(bit)
#define _CLEAR(type,name,bit)       type ## name &= ~ _BV(bit)
#define _TOGGLE(type,name,bit)      type ## name ^= _BV(bit)
#define _GET(type,name,bit)         ((type ## name >> bit) & 1)
#define _PUT(type,name,bit,value)   type ## name = ( type ## name & (  ~ _BV(bit)) ) | ((1 &(unsigned char)value) << bit)

/*these macros are used by the end user*/
#define OUTPUT(pin)     _SET(DDR,pin)
#define INPUT(pin)      _CLEAR(DDR,pin)
#define HIGH(pin)       _SET(PORT,pin)
#define LOW(pin)        _CLEAR(PORT,pin)
#define TOGGLE(pin)     _TOGGLE(PORT,pin)
#define READ(pin)       _GET(PIN,pin)

#define OutX    B,0

/*max delay with _delay_ms is 262.14ms / F_CPU in 32ms for 8MHz
 *so lets iterate this 1ms
 */
void delay1ms(uint32_t ms)
{
    uint32_t i;
    for(i = 0; i < ms; i++)
        _delay_ms(1);
}

void delay1us(uint32_t us)
{
    uint32_t i;
    for(i = 0; i < us; i++)
        _delay_us(1);
}

/*max size for uint16_t is 65,535 not enough for us.
 *max size for uint32_t is 4,294,967,295 thats ok
 */

/*main part of the program*/
int main(void)
{
    OUTPUT(OutX);
    LOW(OutX);

    while(1)
    {
        HIGH(OutX);
        delay1ms(1000);
        LOW(OutX);
        delay1ms(2000);
    }
}
