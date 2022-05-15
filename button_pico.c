#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/sync.h"
#include "hardware/structs/ioqspi.h"
#include "hardware/structs/sio.h"

/*acticate LED's when BOOTSEL button is pressed
 *this code doesn't work if another process is trying to get access,
 *to the flash at the same time, XIP streamer or other cores.
 */
bool __no_inline_not_in_flash_func(get_bootsel_button)()
{
    const uint CS_PIN_INDEX = 1;

    /*Must disable interrupts, as the interrupt handlers may be in the flash,
     *and we are about to temp disable the flash access
     */
    uint32_t flags = save_and_disable_interrupts();

    /*Set chip select to Hi-z*/
    hw_write_masked(&ioqspi_hw->io[CS_PIN_INDEX].ctrl,
                    GPIO_OVERRIDE_LOW << IO_QSPI_QSPI_SS_CTRL_OEOVER_LSB,
                    IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_BITS);

    /*note we can't call into any sleep func in flash*/
    for(volatile int i = 0; i < 1000; ++i);

    /*the HI GPIO registers in SIO can observe and control the 6 QSPI pins.*/
    bool button_state = !(sio_hw->gpio_hi_in &(1u << CS_PIN_INDEX));

    /*need to restore the state of CS(chip select)*/
    hw_write_masked(&ioqspi_hw->[CS_PIN_INDEX].ctrl,
                    GPIO_OVERRIDE_NORMAL << IO_QSPI_GPIO_SS_CTRL_OEOVER_LSB,
                    IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_BITS);

    restore_interrupts(flags);

    return button_state;   
}

/*main part of the pico program*/
int main()
{
    #ifndef PICO_DEFAULT_LED_PIN
    #warning picoboard/button example requires a board with a regualr LED
    #else
        gpio_init(PICO_DEFAULT_LED_PIN);
        gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO__OUT);
        while(true)
        {
            gpio_put(PICO_DEFAULT_LED_PIN, get_bootsel_button() ^ PICO_DEFAULT_LED_PIN_INVERTED);
            sleep_ms(10);
        }
    #endif
}
