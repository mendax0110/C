#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

/*I2C reserves some addresses for special purposes.
 *these are any addresses of the form 000 0xxx or 111 1xxx
 */
bool reserved_addr(uint8_t addr)
{
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

/*main code for the program*/
int main()
{
    /*enable uart so we can print status output*/
    stdio_init_all();
    #if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
    #warning
        puts("Default I2C pins were not defined");
    #else
        /*this example will use I2C0 on the default SDA and SCL pins (GP4, GP5 on a pico)*/
        i2c_init(i2c_default, 100 * 1000);
        gpio_set_functions(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
        gpio_set_functions(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
        gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
        gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
        
        /*make the I2C pins available to picotool*/
        bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));

        printf("\nI2C Bus Scan\n");
        printf(" 0 1 2 3 4 5 6 7 8 9 A B C D E F\n");
        
        for(int addr = 0; addr < (1 << 7); ++addr)
        {
            if(addr % 16 == 0)
            {
                printf("%02x ", addr);
            }

            /*perform a 1-byte dummy read form the probe address.
             *If a slave acks this address, the function returns, 
             *the number of bytes transferred
             */
            int ret;
            uint8_t rxdata;
            if(reserved_addr(addr))
                ret = PICO_ERROR_GENERIC;
            else
                ret = i2c_read_blocking(i2c_default, addr, &rxdata, 1, false);

            printf(ret < 0 ? "." : "@");
            printf(addr % 16 == 15 ? "\n" : " ");
        }
        printf("Done.\n");
        return 0;
    #endif
}
