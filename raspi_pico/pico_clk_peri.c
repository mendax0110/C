/*Rasperry Pi Pico Clock Peri*/
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"

/*define the KiloHerz*/
#define PLL_SYS_KHZ(133 * 1000)

/*main part of the program*/
int main()
{
    /*set the system frequency to 133 MHz.*/
    set_sys_clock_khz(PLL_SYS_KHZ, true);

    /*the previous line automatically detached clk_peri form clk_sys,
     *and attached it to pll_usb, so that clk_peri won't be disturbed by future
     *changes to system clock or system PLL.
     */
    clock_configure(
        clk_peri                                            
        0,                                                  /*no glitches mux*/
        CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS,   /*system PLL on AUX mux*/
        PLL_SYS_KHZ * 1000,                                 /*input frequency*/
        PLL_SYS_KHZ * 1000                                  /*output (must be same as o divider)*/
    );

    /*the serial clock wont't vary from this point onward, so we can configure the uart etc*/
    stdio_init_all();

    puts("Peripheral clock is attached directly to system PLL.");
    puts("We can vary the system clock divisor while printing from the UART:");

    for(uint div = 1; div <= 10; ++div)
    {
        printf("Setting system clock divisor to %u\n", div);
        clock_configure(
            clk_sys,
            CLOCKS_CLK_SYS_CTRL_VALUE_CLKSRC_CLK_SYS_AUX,
            CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS,
            PLL_SYS_KHZ,
            PLL_SYS_KHZ / div
        );

        printf("Measuring system clock with frequency counter:");
        /*note that the numbering of frequency counter sources is not the
         *same as the numbering of clock slice register blocks. If we passed
         *the clk_sys enum here we would actually end up measuring XOSC.)
         */
        printf("%u kHz\n", frequency_count_kHz(CLOCKS_FC0_SRC_VALUE_CLK_SYS));
    }
    return 0;
}