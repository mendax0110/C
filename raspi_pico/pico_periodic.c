#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/irq.h"

/*get time form target.
 *simplest form of getting 64bit time from the timer.
 *isn't safe when called from 2 cores cuz of latching.
 */
static uin64_t get_time(void)
{
    /*reading low latches the high value*/
    uint32_t lo = timer_hw->timelr;
    uint32_t hi = timer_hw->timehr;
    return ((uint64_t) hi << 32u) | lo;
}
/*end get time target*/

/*alarm_standalone[]*/
#define ALARM_NUM 0
#define ALARM_IRQ TIME_IRQ_0

/*alarm interrupt handler*/
static volatile bool alarm_fired;

static void alarm_irq(void)
{
    /*clear the alarm irq*/
    hw_clear_bits(&timer_hw->intr, 1u << ALARM_NUM);

    /*assume alarm 0 has fired*/
    printf("Alarm IRQ fired\n");
    /*enbaled the alarm irq*/
    irq_set_exclusive_handler(ALARM_IRQ, alarm_irq);
    /*enbaled interrupt in block and at processor*/

    /*alarm is only 32 bits so if trying to delay more
     *than that need to be careful and keep track of the upper
     *bits.
     */
    uint64_t target = timer_hw->timerawl + delay_us;

    /*write the lower 32 bits of the target time the alarm which
     *will arm it
     */
    timer_hw->alarm[ALARM_NUM] = (uint32_t) target;
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
        while(!alarm_fired);
    }
}
/*end alarm_standalone[]*/

