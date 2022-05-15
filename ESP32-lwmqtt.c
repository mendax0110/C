/*define the ESP model*/
#if defined(ARDUINO_SAMD_MKR1000) or defined(ESP8266)
    #define __SKIP_ESP32__
#endif

#if defined(ESP32)
    #define __ESP32_MQTT_H__
#endif

#ifdef __SKIP_ESP32__

/*include the librarys*/
#include <Arduino.h>

/*setup the baudrate*/
void setup()
{
    Serial.begin(115200);
}

/*setup the loop*/
void loop()
{
    Serial.println("INPUT 1 2 3");
}

#endif

#ifdef __ESP32_MQTT_H__

/*include the librarys*/
#include "esp32-mqtt.h"

/*setup the communication*/
void setup()
{
    /*put your setup code here, to run once*/
    Serial.begin(115200);
    pinmode(LED_BUILTIN, OUTPUT);
    setupCloudIoT();
}

unsigned long lastMillis = 0;

void loop()
{
    mqtt->loop();
    delay(10); /* <-- this should fix the WiFi Issues*/

    if(!mqttClient->connected())
    {
        connect();
    }

    /*TODO: replace with your code
     *publish a message roughly every second.
     */
    if(millis() - lastMillis > 60000)
    {
        lastMillis = millis();
        /*publishTelemetry(mqttClient, "/sensor", getDefaultSensor());*/
        publishTelemetry(getDefaultSensor());
    }
}
#endif