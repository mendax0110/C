/*include all the librarys*/
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"

/*UART0*/
#define UART0_ID            uart0
#define UART0_BAUD_RATE     115200
#define UART0_TX_GP         0
#define UART0_RX_GP         1
/*UART1*/
#define UART1_ID            uart1
#define UART1_BAUD_RATE     115200
#define UART1_TX_GP         8
#define UART1_RX_GP         9

/*pico LED*/
#define LED_GP   25

/*make the delay*/
void delay(uint32_t ms)
{
    busy_wait_us(ms * 1000);
}

/*flash, then gpio and delay*/
void flash(uint8_t times, uint8_t on = 25, uint8_t off = 100)
{
    for(uint8_t c = 0; c < times; c++)
    {
        gpio_put(LED_GP, 1);
        delay(on);
        gpio_put(LED_GP, 0);
        delay(off);
    }
}

/*main part of the program*/
int main()
{
    /*initialize the GPIO*/
    gpio_init(LED_GP);
    gpio_set_dir(LED_GP, GPIO_OUT);
    flash(1); /*let the rl now we are alive*/

    /*setup the usb as a serial port*/
    stdio_usb_init();
    /*setup the uart0 port as a seperate item*/
    uart_init(UART0_ID, UART0_BAUD_RATE);
    gpio_set_function(UART0_TX_GP, GPIO_FUNC_UART);
    gpio_set_function(UART0_RX_GP, GPIO_FUNC_UART);
    /*setup the uart1 port*/
    uart_init(UART1_ID, UART1_BAUD_RATE);
    gpio_set_function(UART1_TX_GP, GPIO_FUNC_UART);
    gpio_set_function(UART1_RX_GP, GPIO_FUNC_UART);

    delay(1000); /*give item for the usb to be setup*/
    flash(3);    /*time to connect that usb port*/
    delay(2000); /*give item for the usb to ne connected by the user clicking things*/

    puts("USB with debug");
    uart_puts(UART0_ID, "UART0 with debug\n");

    delay(1000); /*give time for the usb to be setup*/

    while(true)
    {
        /*usb serial to uart0 + uart1*/
        uint16_t ch = getchar_timeout_us(100);
        while(ch != PICO_ERROR_TIMEOUT)
        {
            uart_putc_raw(UART0_ID, ch); /*send to uart0*/
            uart_putc_raw(UART1_ID, ch); /*send to uart1*/
            printf("%c", ch);            /*echo back so you can see what you've done*/
            ch = getchar_timeout_us(100);
        }

        /*uart0 to uart1 & usb*/
        while(uart_is_readable_within_us(UART0_ID, 100))
        {
            uint8_t ch = uart_getc(UART0_ID);
            uart_putc_raw(UART1_ID, ch); /*send to uart1*/
            printf("%c", ch);            /*echo to usb*/
        }

        /*uart1 to uart0 & usb*/
        while(uart_is_readable_within_us(UART1_ID, 100))
        {
            uint8_t ch = uart_getc(UART1_ID);
            uart_putc_raw(UART0_ID, ch); /*send to uart0*/
            printf("%c", ch);            /*echo to usb*/
        }
    }

    return 0;
}
