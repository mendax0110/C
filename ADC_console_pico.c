#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

/*define the samples*/
#define N_SAMPLES 1000
uint16_t sample_buf[N_SAMPLES];

/*output for printhelp*/
void printhelp()
{
    puts("\nCommands:");
    puts("c0, ...\t: Select ADC channel n");
    puts("s\t: Sample once");
    puts("S\t: Sample many");
    puts("w\t: Wiggle pins");
}

/*function who is not in flash memory*/
void __not_in_flash_func(adc_capture)(uint16_t *buf, size_t count)
{
    adc_fifo_setup(true, false, 0, false, false);
    adc_run(true);
    for(int i = 0; i < count; i = i + 1)
        buf[i] = adc_fifo_get_blocking();
    adc_run(false);
    adc_fifo_drain();
}

/*main part of the program*/
int main(void)
{
    stdio_init_all();
    adc_init();
    adc_set_temp_sensor_enabled(true);

    /*Set all the pins to input(as far as SIO is concerend)*/
    gpio_set_dir_all_bits(0);
    for(int i = 2; i < 30; ++i)
    {
        gpio_disable_pulls(i);
        gpio_set_input_enabled(i, false);
    }


    printf("\n=======================\n");
    printf("RP2040 ADC and Test Console\n");
    printf("=========================\n");
    printhelp();

    while(1)
    {
        char c = getchar();
        printf("%c", c);
        switch(c)
        {
            case 'c':
                c = getchar();
                printf("%c\n", c);
                if(c < '0' || c > '7')
                {
                    printf("Unknown input channel\n");
                    printhelp();
                }
                else
                {
                    adc_select_input(c - '0');
                    printf("Switched to channel %c\n", c);
                }
                break;
            case 's':
            {
                uint32_t result = adc_read();
                const float conversion_factor = 3.3f / (1 << 12);
                printf("\n0x%03x -> %f V\n", result, result * conversion_factor);
                break;
            }
            case 'S':
            {
                printf("\nStarting capture\n");
                adc_capture(sample_buf, N_SAMPLES);
                printf("Done\n");
                for(int i = 0; i < N_SAMPLES; i = i + 1)
                    printf("%03x\n", sample_buf[i]);
                break;
            }
            case 'w':
                printf("\nPress any key to stop wiggling\n");
                int i = 1;
                while(getchar_timeout_us(0) == PICO_ERROR_TIMEOUT)
                {   
                    /*Pattern: flash all pins for a cycle, 
                    *then scan along pins for one cycle each
                    */
                    i = i ? i << 1 : 1;
                    gpio_put_all(i ? i : ~0);
                }
                gpio_set_dir_all_bits(0);
                printf("Wiggling halted.\n");
                break;
            case '\n':
            case '\r':
                break;
            case 'h':
                printhelp();
                break;
            default:
                printf("\nUnrecognised command: %c\n", c);
                printhelp();
        }       break;
    }
}