#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/tm4c123gh6pm.h"

/*set the values for the registers*/
int registers[8] = {1,1,1,1,1,1,1,1,1}; /*array of integers for writing it serially*/
int i,j,k,r,p;                          /*index variables*/

/*write the register*/
void write_reg()
{
    /*this functions writes the value of register[] to internal registers*/
    GPIOinWrite(GPIO_PORTB_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0 << 2); /*clear the pin2*/
    for(k = 7; k >= 0; k--)
    {
        GPIOinWrite(GPIO_PORTB_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0 << 3); /*clear the pin3*/
        GPIOinWrite(GPIO_PORTB_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,registers[k] << 1);
        GPIOinWrite(GPIO_PORTB_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,1 << 3); /*set the pin3, shifted into 8-bit shift registers(SHCP = HIGH*)*/  
    }

    GPIOinWrite(GPIO_PORTB_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,1 << 2); /*shifted into 8-bit storage register(STCP = High)*/   
}

/*configure the main programm*/
int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_25|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    while(1)
    {
        /*change the values in buffer*/
        for(i = 0; i < 8; i++)
        {
            registers[i] = 0;
            SysCtlDelay(500000);
            write_reg();
        }

        /*reverse order*/
        for(j = 7; j >= 0; j--)
        {
            registers[j] = 1;
            SysCtlDelay(500000);
            write_reg();
        }

        /*reverse order of pattern*/
        for(r = 7; r >= 0; r--)
        {
            registers[r] = 0;
            SysCtlDelay(500000);
            write_reg();
        }

        /*reverse order*/
        for(p = 0; p < 8; p++)
        {
            registers[p] = 1;
            SysCtlDelay(500000);
            write_reg();
        }
    }

return 0;

}
