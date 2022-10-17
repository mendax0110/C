#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"

/*define default led for PWM*/
#ifdef PICO_DEFAULT_LED_PIN

/*make the pwm wrap*/
void on_pwm_wrap()
{
    static int fade = 0;
    static bool going_up = true;
    /*clear the interrupt flag that brought us here*/
    pwm_clear_irq(pwm_gpio_to_slice_num(PICO_DEFAULT_LED_PIN));

    if(going_up)
    {
        ++fade;
        if(fade > 255)
        {
            fade = 255;
            going_up = false;
        }
    }
    else
    {
        --fade;
        if(fade < 0)
        {
            fade = 0;
            going_up = true;
        }
    }
    /*square the fade value to make the LED's brightness appear more linear*/
    pwm_set_gpio_level(PICO_DEFAULT_LED_PIN, fade * fade);   
}
#endif

/*make the main part of the program*/
int main()
{
    /*again define the default pin*/
    #ifdef PICO_DEFAULT_LED_PIN
    #warning pwm/led_fade example requires a board with a regular LED
    #else
        /*tell the led pin that the PWM is in charge of its value*/
        gpio_set_function(PICO_DEFAULT_LED_PIN, GPIO_FUNC_PWM);
        /*figures out which slice we just connected to the LED pin*/
        uint slice_num = pwm_gpio_to_slice_num(PICO_DEFAULT_LED_PIN);

        /*mask our slice IRQ output into the PWM blocks single interrupt line,
         *and register out interrupt handler
         */
        pwm_clear_irq(slice_num);
        pwm_set_irq_enabled(slice_num, true);
        irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap);
        irq_set_enabled(PWM_IRQ_WRAP, true);

        /*get some sensible defaults for the slice config.By default, the
         *counter is allowed to wrap over its mac range(0 to 2**16-1)
         */
        pwm_config config = pwm_get_default_config();
        /*set divider, reduces counter clock to sysclock/this value*/
        pwm_config_set_clkdiv(&config, 4.f);
        /*load the config into our pwm slice and set it running*/
        pwm_init(slice_num, &config, true);

        /*interrupt handler*/
        while(1)
            tight_loop_contents();
    #endif
}