/*include the librarys*/
#include "ESP32PWM.h"

/*define the ESP32 Blud LED on Pin*/
#define LED_BUILTIN         2
#define LED_PWM_FREQUENCY   1000

/*create our PWM device on Pin 9, using the default PWM frequency(500Hz)*/
ESP32PWM led(LED_BUILTIN);

/*to specify the PWM base frequency at contruction, use
 *ESP32PWM led(LED_BUILTIN, LED_PWM_FREQUENCY).
 */
void loop()
{
    /*fade in form min to max in increments of 5 points*/
    for(int fadeValue = 0; fadeValue <= 255; fadeValue += 5)
    {
        /*sets the value range from 0 to 255*/
        led.analogWrite(fadeValue);
        /*wait for 30 milliseconds to see the dimming effect*/
        delay(30);
    }

    /*fade out form max to min in increments of 5 points*/
    for(int fadeValue = 255; fadeValue >= 0; fadeValue -= 5)
    {
        /*sets the value range from 0 to 255*/
        led.analogWrite(fadeValue);
        /*wait for 30 milliseconds to see the dimming effect*/
        delay(30);
    }

    /*to toggle PWM output, use enable() or disable()*/
    led.disable();
    led.analogWrite(255); /*this will not PWM until we enable again*/
    delay(500);
    led.analogWrite(0);
    led.enable();
}
