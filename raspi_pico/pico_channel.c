#include <stdio.h>
#include "hardware/dma.h"
#include "hardware/irq.h"
#include "pio_serialiser.pio.h"

/*pio sends one bit per 10 system clock cycles. DMA sends the same 32-bit
 *value 10 000 times before halting.
 */
#define PIO_SERIAL_CLKDIV   10.f
#define PWM_REPEAT_COUNT    10000
#define N_PWM_LEVELS        32

int dma_chan;

void dma_handler()
{
    static int pwm_level = 0;
    static uint32_t wavetable[N_PWM_LEVELS];
    static bool first_run = true;
    /*entry number 'i' has 'i' one bits and '(32  - i)' zero bits*/
    if(first_run)
    {
        first_run = false;
        for(int i = 0; i < N_PWM_LEVELS; ++i)
            wavetable[i] = ~(~0u << i);
    }

    /*clear the interrupt request*/
    dma_hw->ints0 = 1u << dma_chan;
    /*give the channel a new wave table entry to read form, and re-trigger it*/
    dma_channel_set_read_addr(dma_chan, &wavetable[pwm_level], true);

    pwm_level = (pwm_level + 1) % N_PWM_LEVELS;
}

int main()
{
    #ifdef PICO_DEFAULT_LED_PIN
        #warning dma/channel_irq example requires a board with a regular LED
    #else
        /*setup a PIO state machine to serialise out bits*/
        uint offset = pio_add_program(pio0, &pio_serialiser_program);
        pio_serialiser_program_init(pio0, 0, offset, PICO_DEFAULT_LED_PIN, PIO_SERIAL_CLKDIV);

        /*configure a channel to write the same word (32 bits) repeatedly to PIO0
         *SM0's TX FIFO, paced by the data request signal form that peripheral.
         */
        dma_chan = dma_claim_unused_channel(true);
        dma_channel_config c = dma_channel_get_default_config(dma_chan);
        channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
        channel_config_set_read_increments(&c, false);
        channel_config_set_dreq(&c, DREQ_PIO0_TX0);

        dma_channel_configure(
            dma_chan,
            &c,
            &pio0_hw->txf[0], /*write address*/
            NULL,             /*dont provide a read address yet*/
            PWM_REPEAT_COUNT, /*write the same value many times, then halt and interrupt*/
            false             /*dont start yet*/
        );

        /*tell the DMA to raise IRQ line 0 when the channel finished a block*/
        dma_channel_set_irq0_enabled(dma_chan, true);

        /*configure the processor to run dma_handler() when DMA IRQ 0 is asserted*/
        irq_set_exclusive_handler(DMA_IRQ_0, dma_handler);
        irq_set_enabled(DMA_IRQ_0, true);

        /*manually call the handler once, to trigger the first transfer*/
        dma_handler();

        /*everthing else from this point is interrupt-driven*/
        while(true)
            tight_loop_contents();
    #endif
}