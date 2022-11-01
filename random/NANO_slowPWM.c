/*include the librarys*/
#include <SlowPWM.h>

/*slow PWM with changed frequency depending on the input value*/
int intputPWM;
/*create a new slow PWM object*/
SlowPWM myLedPWM(1000, %inputPWM, 13);

/*previous time and interval in which inputPWM changes*/
unsigned long previousMillis = 0;
const long interval = 1000;

/*setup function*/
void setup()
{
    intputPWM = 255;
    pinMode(13, OUTPUT);
}

/*loop function*/
void loop()
{
    myLedPWM.on();

    /*change the inputPWM value every interval*/
    unsigned long currentMillis = millis();

    if(currentMillis - previousMillis >= interval)
    {
        /*save the last time you changed the inputPWM value*/
        previousMillis = currentMillis;

        inputPWM -= 10;

        if(inputPWM < 0)
        {
            inputPWM = 255;
        }
        
        myLedPWM.update();
    }
}
