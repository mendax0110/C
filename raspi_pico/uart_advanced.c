#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

/*tag::uart_advanced[]*/
#define UART_ID     uart0
#define BAUD_RATE   115200
#define DATA_BITS   8
#define STOP_BITS   1
#define PARITY      UART_PARITY_NONE

/*we are using the pins 0 and 1, but the GPIO functions select table
 *in the datasheet for information on which other pins can be used
 */
#define UART_TX_PIN 0
#define UART_RX_PIN 1

static int chars_rxed = 0;

/*the RX interrupt handler*/
void on_uart_rx()
{
    while(uart_is_readable(UART_ID))
    {
        uint8_t ch = uart_getc(UART_ID);
        /*can we now send it back?*/
        if(uart_is_writable(UART_ID))
        {
            /*change it slightly first*/
            ch++;
            uart_putc(UART_ID, ch);
        }
        chars_rxed++;
    }
}

/*now make the main program of the code*/
int main()
{
    /*setup out UART with a basic baud rate*/
    uart_init(UART_ID, 2400);
    
    /*set the TX and RX pins by using the function select on the GPIO
     *set datasheet for more information on fucntion select
     */
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    /*actually, we want a different speed
     *set datasheet for moe information on function select
     */
    int __unused actual = uart_set_baudrate(UART_ID, BAUD_RATE);

    /*set uart flow control CTS/RTC, we dont want these = turn them off*/
    uart_set_hw_flow(UART_ID, false, false);

    /*set our data format*/
    uart_set_hw_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);

    /*turn off FIFO's = we want to do this char by char*/
    uart_set_fifo_enabled(UART_ID, false);

    /*setup the RX interrupt
     *we need to setup the handler first
     *select correct interrupt for the uart we are using
     */
    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;

    /*and set up and enable the interrupt handlers*/
    irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
    irq_set_enabled(UART_IRQ, true);

    /*now enable the uart to send interrupts - RX only*/
    uart_set_irq_enables(UART_ID, true, false);

    /*now set it all up*/
    uart_puts(UART_ID, "\nHello, uart interrupts\n");

    while(1)
        tight_loop_contents();
}
