/*incude the librarys*/
#include <PinChangeInterrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>

/*define the LED and the switch*/
#define LED     3 //D3
#define SWITCH  4 //D4

/*setup the pinmode*/
void setup()
{
    pinMode(LED, OUTPUT);
    pinMode(SWITCH, INPUT_PULLUP); //internal Pull-Up
    /*vaild interrupt modes are: RISING,FALLING,CHANGE*/
    attachPCINT(digitalPinToPinChangeInterrupt(SWITCH), wakeUpNow, FALLING);
}

/*setup the loop*/
void loop()
{
    digitalWrite(LED, HIGH);
    delay(2000);
    digitalWrite(LED, LOW);
    delay(2000);
    gotToSleep();
}

void wakeUpNow()
{
    /*here can you execute code after the wake-up before returning
     *to the loop function
     */
}

void (gotToSleep)
{
    /*you have to decive which mode you want to use.
     *There are 5 different modes.
     */
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    ADCSRA = 0; /*turn off the ADC*/
    power_all_disable(); /*power off ADC, Timer 0,1 serial etc*/
    sleep_enable(); /*sleep*/
    sleep_cpu(); /*sleep*/
    //--------------------------THE PROGRAM FROM HERE AFTER WAKING UP---------------------//
    sleep_disable();
    power_all_enable(); /*everything back online*/
}
