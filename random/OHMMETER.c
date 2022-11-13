/*This is a simple Ohmmeter
 *define the pins and the values
 */
int analogPin       = 0;
int raw             = 0;
int Vin             = 5;
float   Vout        = 0;
float   R1          = 2000;
float   R2          = 0;
float   buffer      = 0;

/*setup the serial communication*/
void setup()
{
    Serial.begin(9600);
}

/*now do the math and print the serial output*/
void loop()
{
    /*read the analog value*/	
    raw = analogRead(analogPin);

    if(raw)
    {
        buffer  = raw * Vin;
        Vout    = (buffer) / 1024.0;
        buffer  = (Vin/Vout) - 1;
        R2      = R1 * buffer;

        /*print the output*/
        Serial.print("Vout: ");
        Serial.println(Vout);
        Serial.print("R2: ");
        Serial.println(R2);

        /*now do the delay*/
        delay(1000);
    }
}
