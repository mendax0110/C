/*rasperry pi pico clock 48MHz*/
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pll.h"
#include "hardware/clocks.h"
#include "hardware/structs/pll.h"
#include "hardware/structs/clocks.h"

/*measure the frequence*/
void measure_freqs(void)
{
    uint f_pll_sys  = frequency_count_khz(CLOCK_FC0_SRC_VALUE_PLL_SYS_CLKSRC_PRIMARY);
    uint f_pll_usb  = frequency_count_khz(CLOCK_FC0_SRC_VALUE_PLL_USB_CLKSRC_PRIMARY);
    uint f_rosc     = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_ROSC_CLKSRC);
    uint f_clk_sys  = frequency_count_khz(CLOCK_FC0_SRC_VALUE_CLK_SYS);
    uint f_clk_peri = frequency_count_khz(CLOCK_FC0_SRC_VALUE_CLK_PERI);
    uint f_clk_usb  = frequency_count_khz(CLOCK_FC0_SRC_VALUE_CLK_USB);
    uint f_clk_adc  = frequency_count_khz(CLOCK_FC0_SRC_VALUE_CLK_ADC);
    uint f_clk_rtc  = frequency_count_khz(CLOCK_FC0_SRC_VALUE_CLK_RTC);

    printf("pll_sys     = %dkHz\n", f_pll_sys);
    printf("pll_usb     = %dkHz\n", f_pll_usb);
    printf("rosc        = %dkHz\n", f_rosc);
    printf("clk_sys     = %dkHz\n", f_clk_sys);
    printf("clk_peri    = %dkHz\n", f_clk_peri);
    printf("clk_usb     = %dkHz\n", f_clk_usb);
    printf("clk_adc     = %dkHz\n", f_clk_adc);
    printf("clk_rtc     = %dkHz\n", f_clk_rtc);

    /*can't measure clk_reg / xosc as it is the ref*/
}

/*main part of the program*/
int main()
{
    stdio_init_all();

    printf("Message to the Clock!\n");

    measure_freqs();

    /*change clk_sys to be 48MHz. The simplest way is to take this from
     *PLL_USB which has a source frequency of 48MHz.
     */
    clock_configure(clk_sys,
                    CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX,
                    CLOCK_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB,
                    48 * MHz,
                    48 * MHz);

    /*turn off the PLL sys for good measure*/
    pll_deinit(pll_sys);

    /*clk peri is clocked from clk_sys so need to change clk_peri's freq*/
    clock_configure(clk_peri,
                    0,
                    CLOCK_CLK_PERI_CTRL_AUXSRC_VALUE_CLK_SYS,
                    48 * MHz,
                    48 * MHz);

    /*re init uart now that clk_peri has changed*/
    stdio_init_all();

    measure_freqs();
    printf("Message: 48MHz");

    return 0;
}
