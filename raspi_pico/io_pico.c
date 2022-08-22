#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/structs/watchdog.h"

/*this shows the effect of byte and halfword writes on IO registers*/
int main()
{
    stdio_init_all();

    /*we'll use watchdog_scratch0 as a convenient 32 bit r/w register*/
    io_rw_32 * scratch32 = &watchdog_w->scratch[0];
    /*alias the scratch register as two halfwords at offsets +0x0 and +0x2*/
    volatile uint16_t *scratch16 = (volatile uint16_t *) scratch32;
    /*alias the scratch register as four bytes af offsets +0x0, +0x1, +0x2, +0x3*/
    volatile uint8_t *scratch8 = (volatile uint8_t *) scratch32;

    /*show that we can r/w the scratch as normal*/
    printf("Writing 32 bit value\n");
    *scratch32 = 0xdeadbeef;
    printf("Should be 0xdeadbeef: 0x%08x\n", *scratch32);

    /*we can do narrow reads just fine --IO registers treat this as 32 bit
     *read, and the processor/DMA wil pick out the correct byte lanes base
     *on transfer size and address LSB's
     */
    printf("\nReading back 1 byte at a time\n");
    printf("Should be ef be ad de: %02x %02x %02x %02x\n",
            scratch8[0], scratch8[1], scratch8[2], scratch8[3]);

    /*the cortex-m0+ and the RP2040 dma replicate byte writes across the bus,
     *and IO registers will sample the entire r/w bus always.
     */
    printf("\nWriting 8 bit value 0xa5 at offset 0\n");
    scratch8[0] = 0xa5;
    /*read back the whole scratch register in one go*/
    printf("Shoudl be 0xa5a5a5a5: 0x%08x\n", *scratch32);

    /*the IO register ignores the address LSB's [1:0] as well as the transfer
     *size, so it doesn't matter what byte offset we use.
     */
    printf("\nWriting 8 bit value at offset 1\n");
    scratch8[1] = 0x3c;
    printf("Shoudl be 0x3c3c3c3c: 0x%08x\n", *scratch32);

    /*halfword writes are also replicated across the writes data bus*/
    printf("\nWriting 16 bit value at offset 0\n");
    scratch16[0] = 0xf00d;
    printf("Should be 0xf00df00d: 0x%08x\n", *scratch32);
}
