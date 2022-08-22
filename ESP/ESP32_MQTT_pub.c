/*include the librarys*/
#include "UbidotsEsp32Mqtt.h"

/*define the constants*/
const char *UBIDOTS_TOKEN = "";     /*here is to place to put your token*/
const char *WIFI_SSID = "";         /*here can you place your SSID*/
const char *WIFI_PASS = "";         /*here can you place your PASWD*/
const char *DEVIE_LABEL = "";       /*put here your label(this will be published)*/
const char *VARIABLE_LABEL = "";    /*put here your variable Lable(this will be published)*/

const int PUBLISH_FREQUENCY = 5000; /*update rate in milliseconds*/

unsigned long timer;
uint8_t analogPin = 34; /*the pin used to read data from GPIO34 ADC_CH6*/

Ubidots ubidots(UBIDOTS_TOKEN);

/*Auxiliar Functions*/
void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived[");
    Serial.print(topic);
    Serial.print("]");
    for(int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i])
    }
    Serial.println();
}

/*main functions*/
void setup()
{
    /*please put here your code, to run once*/
    Serial.begin(115200);
    /*ubidots.setDebug(true)*/
    ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
    ubidots.setCallback(callback);
    ubidots.setup();
    ubidots.reconnect();

    timer = millis();
}

void loop()
{
    /*put your main code here, to run and repeat*/
    if(!ubidots.connected())
    {
        ubidots.reconnect();
    }
    if(abs(millis() - timer) > PUBLISH_FREQUENCY) /*triggers the routine every 5 seconds*/
    {
        float value = analogRead(analogPin);
        ubidots.add(VARIABLE_LABEL, value); /*insert your variable lables and value to be send*/
        ubidots.publish(DEVIE_LABEL);
        timer = millis();
    }
    ubidots.loop();
}
