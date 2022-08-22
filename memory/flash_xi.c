#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/dma.h"
#include "hardware/regs/addressmap.h"
#include "hardware/structs/xip_ctrl.h"

#include "random_test_data.h"

/*XIP has some internal hardware that can stream a linear access sequence
 *to a DMable FIFO, while the system is still doing random accesses on flash
 */

uint32_t buf[count_of(random_test_data)];

/*Start of the main progam*/
int main()
{
    stdio_init_all();
    for(int i = 0; i < count_of(random_test_data); ++i)
        buf[i] = 0;

    if((uint32_t) &random_test_data[0] >= SRAM_BASE)
    {
        printf("You need to run this example form the flash!\n");
        exit(-1);
    }

    printf("Starting stream from %p\n", random_test_data);
    /*tag::start_stream[]*/
    while(!(xip_ctrl_hw->stat & XIP_STAT_FIFO_EMPTY))
        (void) xip_ctrl_hw->stream_fifo;
    xip_ctrl_hw->stream_addr = (uint32_t) &random_test_data[0];
    xip_ctrl_hw->stream_ctr = count_of(random_test_data);
    /*tag::stop_stream[]*/

    printf("Starting DMA\n");
    /*tag::start_DMA[]*/
    const uint dma_chan = 0;
    dma_channel_config cfg = dm_channel_get_default_config(dma_chan);
    channel_config_set_read_increment(&cfg, false);
    channel_config_set_write_increment(&cfg, true);
    channel_config_set_dreq(&cfg, DREQ_XIP_STREAM);
    dm_channel_configure (

            dma_chan,
            &cfg,
            (void *) buf                    /*write addr*/
            (const void *) XIP_AUX_BASE,    /*read addr*/
            count_of(random_test_data),     /*transfer count*/
            true                            /*start immediately*/

    );

    /*end::start_dma[]*/

    dma_channel_wait_for_finish_blocking(dma_chan);

    printf("DMA complete\n");

    bool mismatch = false;
    for(int i = 0; i < count_of(random_test_data); ++i)
    {
        if(random_test_data[i] != buf[i])
        {
            printf("Data mismatch: %08x (actual) != %08x (expected)\n", buf[i], random_test_data[i]);
            mismatch = true;
            breaK;
        }
        printf(("%o8x%c", buf[i], i % 8 == 7 ? '\n' : ' ');
    }
    if(!mismatch)
        printf("Data check OK!\n");
}
