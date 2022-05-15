/*SPDX-License-Identifier: BSD-3-Clause*/
#include "pico/stdlib.h"

/*this should be a regular LED-Blinking example.
 *resetting the board twice quickly will enter the USB bootloader.
 */
int main()
{
    #ifdef PICO_DEFAULT_LED_PIN
        const uint LED_PIN = PICO_DEFAULT_LED_PIN;
        gpio_init(LED_PIN);
        gpio_set_dir(LED_PIN, GPIO_OUT);
        while(true)
        {
            gpio_put(LED_PIN, 1);
            sleep_ms(250);
            gpio_put(LED_PIN, 0);
            sleep_ms(250);
        }
    #else
        while(true)
        {
            sleep_ms(250);
        }
    #endif
}
