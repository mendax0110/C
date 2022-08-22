/*include the needed librarys*/
#include <ESP8266WiFi.h>

/*GPIO definitions*/
#define D0  16
#define D1  5
#define D2  4
#define D3  0
#define D4  2
#define D5  14
#define D6  12
#define D7  13
#define D8  1
#define RX  3       /*when using UART(serial) dont touch the RX*/
#define TX  1       /*when using UART(serial) dont touch the RX*/
#define S3  10      /*doesnt work on D12*/
#define S2  9       /*doesnt work on D11*/
#define CMD 11
#define CLK 6

/*pins from 1 to 12 is PWM ~ pins only(D1,D2,D3,D4,D6) are stable
 *don't use any ohter pins for pwm only -> (D1, D2, D4, D6)
 */

void pwmTest(int pin);

/*setup the serial commmunication*/
void setup()
{
    Serial.begin(115200);
    pinMode(2,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(12,OUTPUT);
}

void loop()
{
    Serial.println("\n----------------------------");
    
    Serial.println("pwm test for D4");
    pwmTest(2);

    Serial.println("pwm test for D2");
    pwmTest(4);

    Serial.println("pwm test for D1");
    pwmTest(5);

    Serial.println("pwm test for D6");
    pwmTest(12);
}

/*GPIO testin Functions*/
void pwmTest(int pin)
{
    Serial.print("PIN");
    Serial.print(pin);
    Serial.println("PWM testing");
    delay(5000);

    for(int i = 0; i <= 255; i++)
    {
        analogWrite(pin,i);
        delay(50);
    }

    Serial.println("------------------------------");
}
