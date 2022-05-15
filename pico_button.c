#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/sync.h"
#include "hardware/structs/ioqspi.h"
#include "hardware/structs/sio.h"

/*this code should force the pico LED to blink*/
bool __no_inline_not_in_flash_func(get_bootsel_button)()
{
    const uint CS_PIN_INDEX = 1;

    /*must disable interrupts first, as the interrupt handlers my be in the flash
     *and we are about to temp disable flash access.
     */
    uint32_t flags = save_and_disable_interrupts();

    /*set chip select to Hi-Z*/
    hw_write_masked(&ioqspi_hw->io[CS_PIN_INDEX].ctrl,
                    GPIO_OVERRIDE_LOW << IO_QSPI_GPIO_SS_CTRL_OEOVER_LSB,
                    IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_BITS);

    /*please note that we can't call into any sleep functions right now*/
    for(volatile int i = 0; i < 1000; ++i)

    /*the HI-GPIO registers in SIO can observe and control the 6 QSPI pins.
     *note the button pulls the pin *low* when pressed.
     */
    bool button_state =! (sio_hw->gpio_hi_in & (1u << CS_PIN_INDEX));

    /*need to restore the state of chop select, else we are going to have a 
     *bad time when we return to code in flash.
     */
    hw_write_masked(&ioqspi_hw->io[CS_PIN_INDEX].ctrl,
                    GPIO_OVERRIDE_NORMAL << IO_QSPI_GPIO_SS_CTRL_OEOVER_LSB,
                    IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_BITS);

    restore_interrupts(flags);

    return button_state;
}

/*main part of the program*/
int main()
{
    #ifdef PICO_DEFAULT_LED_PIN
        #warning picoboard/button example requires a board with a regular LED
    #else
        gpio_init(PICO_DEFAULT_LED_PIN);
        gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
        while(true)
        {
            gpio_put(PICO_DEFAULT_LED_PIN, get_bootsel_button() ^ PICO_DEFAULT_LED_PIN_INVERTED);
            sleep_ms(10);
        }
    #endif
}
