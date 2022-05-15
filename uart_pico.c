#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/pio.h"
#include "hardware/uart.h"
#include "uart_rx.pio.h"

/*this sketch uses
 * UART1 to transmit some text
 * PIO state machine to receive that text
 * print this text to the console(uart0)
 */

#define SERIAL_BAUD PICO_DEFAULT_UART_BAUD_RATE
#define HARD_UART_INST uart1

/*I've need a wire form GPIO4 -> GPIO3*/
#define HARD_UART_TX_PIN 4
#define PIO_RX_PIN 3

/*ask the core 1 to print a string, to make things easier on core 0*/
void core1_main()
{
    const char *s = (const char *) multicore_fifo_pop_blocking();
    uart_puts(HARD_UART_INST, s);
}

/*main part of the program*/
int main()
{
    /*console output (also uart)*/
    setup_default_uart();
    printf("Starting PIO UART RX example\n");

    /*setup the hard UART, now we are going to print charachters*/
    uart_init(HARD_UART_INST, SERIAL_BAUD);
    gpio_set_functions(HARD_UART_TX_PIN, GPIO_FUNC_UART);

    /*setup the state machine, now we are going to use to receive them*/
    PIO pio = pio0;
    uint sm = 0;
    uint offset = pio_add_program(pio, &uart_rx_program);
    uart_rx_program_init(pio, sm, offset, PIO_RX_PIN, SERIAL_BAUD);

    /*tell the core1 to print some text to uart1 as fast as it can do it*/
    multicore_launch_core1(core1_main);
    const char *text = "This is the important message from the PIO! (Plus 2 UARTs and 2 cores, for complex reasons)\n";
                        multicore_fifo_push_blocking((uint32_t) text);

    /*echo characters received from PIO to the console*/
    while(true)
    {
        char c = uart_rx_program_getc(pio, sm);
        putchar(c);
    }
}

