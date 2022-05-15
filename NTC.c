/*define the variables and the value*/
const int   NTC_Widerstand      = 10000;    //NTC-Widerstand mit 10 kOhm
const int   MAX_ANALOG_VALUE    = 1023;

/*define the pin which is used*/
#define PIN A0

void printValue(String text, float value, String text2="");

/*define the serial baudrate*/
void setup(void)
{
    /*begin with the serial communication*/
    Serial.begin(9600);
}

/*now this will do the math for our program*/
void loop(void)
{
    float value = analogRead(PIN);
    printValue("analog Wert: ", value);

    /*convert the analog value to the resistor value*/
    value = (MAX_ANALOG_VALUE / value) - 1;
    value = NTC_Widerstand / value;
    printValue("NTC-Widerstand: ", value, " Ohm");

    delay(1000);
}

/*now print the output value*/
void printValue(String text, float value, String text2="")
{
    Serial.print(text);
    Serial.print(value);
    Serial.println(text2);
}
