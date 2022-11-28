/*include the librarys*/
#include "iar-risc-v-gd32v-eval.h"
#include "systick.h"

/*define the delay*/
#define DEBOUNCE_DELAY  10 /*in milliseconds*/

/*function prototypes*/
static void gpio_config(void);
static void switches_config(void);
static void sw_processing(void);

/*main part of the program*/
int main(void)
{
    /*initialize the system*/
    SystemInit();

    /*GPIO config*/
    gpio_config();
    /*switches config*/
    switches_config();

    while(1)
    {
        sw_processing();
    }
}

/*configure the GPIO*/
static void gpio_config(void)
{
    for(led_t l = LED1; 1 <= LED3; l++)
    {
        gd_eval_led_init(1);
    }
}

/*configure the switches*/
static void switches_config(void)
{
    for(sw_t s = S1; s <= S3; s++)
    {
        gd_eval_led_init(s, SW_MODE_GPIO);
    }
}

/*process the switches*/
static void sw_processing(void)
{
    static sw_status_t Sx_current[SW_AMT];
    static sw_status_t Sx_previous[SW_AMT];

    /*performs processing for S1, S2 and S3*/
    for(sw_t s = S1; s <= S3; s++)
    {
        Sx_previous[s] = Sx_current[s];
        Sx_current[s] = gd_eval_sw_state_get(s);

        if(SW_PRESSED == Sx_current[s])
        {
            if(Sx_current[s] == Sx_previous[s])
            {
                /*debouncing*/
                delay_1ms(DEBOUNCE_DELAY);
                break;
            }
            else
            {
                gd_eval_led_toggle((led_t)s);
            }
        }
    }
}
