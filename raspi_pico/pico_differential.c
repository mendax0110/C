/*include the header file*/
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "differential_manchester_pio.h"

/*differential serial transmit/receive example
 *need to connect a wire from GPIO2 -> GPIO3
 */

const uint pin_tx = 2;
const uint pin_rx = 3;

/*main function*/
int main()
{
    stdio_init_all();

    /*set up the pins*/
    uint sm_tx = 0;
    uint sm_rx = 1;

    uint offset_tx = pio_add_program(pio0, &differential_manchester_tx_program);
    uint offset_rx = pio_add_program(pio0, &differential_manchester_rx_program);

    /*print the tx and the rx*/
    printf("Transmit program loaded at %d\n", offset_tx);
    printf("Receive program loaded at %d\n", offset_rx);

    /*configure state machines, set bit rate at 5 Mbps*/
    differential_manchester_tx_program_init(pio0, sm_tx, offset_tx, pin_tx, 125.f / (16 * 5));
    differential_manchester_rx_program_init(pio0, sm_rx, offset_rx, pin_rx, 125.f / (16 * 5));

    /*set up the state machines*/
    pio_sm_set_enabled(pio0, sm_tx, true);
    pio_sm_put_blocking(pio0, sm_tx, 0);
    pio_sm_put_blocking(pio, sm_tx, 0x0ff0a55a);
    pio_sm_put_blocking(pio, sm_tx, 0x12345678);
    pio_sm_set_enabled(pio0, sm_tx, true);

    /*print the received data*/
    for(int i = 0; i < 3; i++)
    {
        printf("Received: 0x%08x\n", pio_sm_get_blocking(pio0, sm_rx));
    }
}