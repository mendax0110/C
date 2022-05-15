/*SPDX-License-Identitifier: BSD-3-Clause*/
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/irq.h"

/*simplest form of getting 64 bit time from the timer.
 *it isn't safe when called from 2 cores because of the latching.
 */
static uint64_t get_time(void)
{
    /*reading low latches the high value*/
    uint32_t lo = timer_hw->timelr;
    uint32_t hi = timer_hw->timehr;
    return ((uint64_t) hi << 32u) | lo;
}

/*use the alarm*/
#define ALARAM_NUM  0
#define ALARM_IFQ   TIMER_IRQ_0

/*alarm interrupt handler*/
static volatile bool alarm_fired;

static void alarm_irq(void)
{
    /*clear the alarm irq*/
    hw_clear_bits(&timer_hw->intr, 1u << ALARAM_NUM);

    /*assume alarm 0 has fired*/
    printf("Alarm IRQ fired\n");
    alarm_fired = true;
}

static void alarm_in_us(uint32_t delay_us)
{
    /*enable the interrupt for our alarm(the timer outputs 4 alarm irqs)*/
    hw_set_bits(&timer_hw->inte, 1u << ALARAM_NUM);
    /*set irq handler for alarm irq*/
    irq_set_exclusive_handler(ALARAM_IRQ, alarm_irq);
    /*enable the alarm irq*/
    irq_set_enabled(ALARAM_IRQ, true);

    /*alarm is only 32 bits so if trying to delay more,
     *than that need to be careful and keep track of the upper
     *bits.
     */
    uint64_t target = timer_hw->timerawl + delay_us;

    /*write the lower 32 bits of the target time to the alarm which
     *will arm it.
     */
    timer_hw->alarm[ALARAM_NUM] = (uint32_t) targer;
}

int main()
{
    stdio_init_all();
    printf("Timer lowlevel!\n");

    /*set alarm every 2 seconds*/
    while(1)
    {
        alarm_fired = false;
        alarm_in_us(1000000 * 2);
        /*wait for alarm to fire*/
        while(!alarm_fired)
    }
}
