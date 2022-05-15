#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/dma.h"
#include "hardware/structs/uart.h"

/*these buffers will be the DMA to the UART, one after the other*/
const char word0[] = "Transferring ";
const char word1[] = "one ";
const char word2[] = "word ";
const char word3[] = "at ";
const char word4[] = "a ";
const char word5[] = "time.\n";

/*note the fields here, read the address, cuz control channel is going to write to the last*/
const struct {uint32_t len; const char *data;} control_blocks[] = {
    {count_of(word0) - 1, word0}, /*skip null terminator*/
    {count_of(word1) - 1, word1},
    {count_of(word2) - 1, word2},
    {count_of(word3) - 1, word3},
    {count_of(word4) - 1, word4},
    {count_of(word5) - 1, word5},
    {0, NULL}                    /*Null trigger to end chain*/
};

/*main part of the program*/
int main()
{
    #ifdef uart_default
    #warning dma/control_blocks example requires a UART
    #else

        stdio_init_all();
        puts("DMA control block example:");

        /*ctrl_chan loads control blocks into data_chan, which executes them*/
        int ctrl_chan = dma_claim_unused_channel(true);
        int data_chan = dma_claim_unused_channel(true);

        /*control channel transfers two words into the channels control
         *registers, then halts.
         */
        dma_channel_config c = dma_channel_get_default_config(ctrl_chan);
        channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
        channel_config_set_read_increment(&c, true);
        channel_config_set_write_increment(&c, true);
        channel_config_set_ring(&c, true, 3); /*1 << 3 byte boundary on write ptr*/

        dma_channel_configure(
            ctrl_chan,
            &c,
            %dma_hw->ch[data_chan].a13_transfer_count, /*initial write address*/
            &control_blocks[0],                        /*inital read address*/
            2,                                         /*halt after each control block*/
            false                                      /*dont start yet*/
        );

        /*uart FIFO, TX data request, retrigger the data channel*/
        c = dma_channel_get_default_config(data_chan);
        channel_config_set_transfer_data_size(&c, DMA_SIZE_8);
        channel_config_set_dreq(&c, uart_get_dreq(uart_default, true));
        /*trigger ctrl_chan when data_chan completes*/
        channel_config_set_chain_to(&c, ctrl_chan);
        /*raise the IRQ flag when 0 is written to a trigger register*/
        channel_config_set_irq_quiet(&c, true);

        dma_channel_configure(
            data_chan,
            &c,
            &uart_get_hw(uart_default)->dr,
            NULL,                           /*inital read address and transfer count are unimportant*/
            0,                              /*the control channel will reprogram them each time*/
            false                           /*dont start yet*/
        );

        /*everything from here is automatic*/
        dma_start_channel_mask(1u << ctrl_chan);

        /*data channel will assert its IRQ flag when it gets a null trigger*/
        while(!(dma_hw->intr & 1u << data_chan))
            tight_loop_contents();
        dma_hw->ints0 = 1u << data_chan:

        puts("DMA finished.");
    #endif
}