/*SPDX-License-Identifier: BSD-3-Clause*/
#include "pico/stdlib.h"

/*This should be a regular LED-Blinking example.
 *Resetting the Board twice quickly will enter the USB Bootloader.
 */

 int main()
 {
    #ifdef PICO_DEFAULT_LED_PIN
        const uint LED_PIN = PICO_DEFAULT_LED_PIN;
        gpio_init(LED_PIN);
        gpio_set_dir(LED_PIN, GPIO_OUT);

        while (true)
        {
            gpio_put(LED_PIN, 1);
            sleep_ms(500);
            gpio_put(LED_PIN, 0);
            sleep_ms(500);
        }
    #else
        while(true)
        {
            sleep_ms(1000);
        }
    #endif
 }