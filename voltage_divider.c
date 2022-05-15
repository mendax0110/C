/*This is a simple voltage divider with an arduino mega2560
 *and two resistors and a potentiometer and a LED
 */
int analogPin   = A3;   /*potentiometer wiper(middle Terminal) connected to analogPin 3*/
int val         = 0;    /*outsides leads to ground and +5 volts*/
int LED         = 3;    /*variable to store the value read*/

/*setup the serial communication*/
void setup()
{
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    val = analogRead(analogPin);    /*read the voltage of input pin 3*/
    Serial.println(val);            /*debug value*/

    if(val < 110)
    {
        digitalWrite(LED, HIGH);
        delay(1000);
        digitalWrite(LED, LOW);
        delay(1000);                /*blink the LED 1/sec*/
    }

    if(val > 400)
    {
        digitalWrite(LED, HIGH);
        delay(300);
        digitalWrite(LED, LOW);
        delay(300);                 /*blink the LED 2/sec*/
    }
    else
    {
        digitalWrite(LED, LOW);     /*turn off the LED*/
    }
}
