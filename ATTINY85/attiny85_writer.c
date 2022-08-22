/*include the librarys*/
#include <Wire.h>

/*define the communication*/
#define USE_SERIAL  Serial

/*setup the serial begin and communication*/
void setup()
{
    Wire.begin();
    USE_SERIAL.begin(9600);
    USE_SERIAL.println("Main program is starting...");
    USE_SERIAL.println("Set value");
}

/*loop for read/write*/
void loop()
{
    String preVal = x;
    if(USE_SERIAL.avaiable())
    {
        x = USE_SERIAL.readString();
        delay(200);
    }

    if(preVal != x)
    {
        char buffer[4];
        x.toCharArray(buffer, 4);
        Wire.beginTransmission(13);
        Wire.write(buffer);
        Wire.endTransmission();
        USE_SERIAL.print("Data sent to ATtiny Device: ");
        USE_SERIAL.println(buffer);
        Wire.requestFrom(0x13,1);

        while(Wire.avaiable())
        {
            int c = Wire.read();
        }
    }
    delay(50);
}