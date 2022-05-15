#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

/*declare your WIFI Credentials*/
const char* ssid = "Your SSID";
const char* password = "Your Password";

/*define the LED Blink PIN*/
int ledPin = 2;

/*try to detect the OTA device with the Arduino SW*/
WiFiServer TelnetServer(8266);

void setup()
{
    /*begin the search for the OTA device*/
    TelnetServer.begin();

    Serial.begin(115200);
    Serial.println("Booting...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while(WiFi.waitforConnectResult() != WL_CONNECTED)
    {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }

    /*the default port is 8266
     *ArduinoOTA.setport(8266)
     *hostname default to esp8266-CHIPID
     *NO AUTH
     */
    ArduinoOTA.onStart([]()
    {
        Serial.println("OTA Start");
    });
    ArduinoTOA.onEnd([]()
    {
        Serial.println("OTA End");
        Serial.println("Rebooting...");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
    {
        Serial.println("Progress: %u%%\r\n", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error)
    {
        Serial.printf("Error[%u]: ", error);
        if(error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if(error == OTA_BEGIN_ERROR) Serial.prinln("Begin Failed");
        else if(error == OTA_CONNECT_ERROR) Serial.prinln("Connect Failed");
        else if(error == OTA_RECEIVE_ERROR) Serial.prinln("Receive Failed");
        else if(error == OTA_END_ERROR) Serial.prinln("End Failed");
    });
    ArduinoOTA.begin();
    Serial.println("Ready");
    Serial.print("IP address: ");
    Serial.prinln(WiFi.localIP());

    /*set LED PIN as an output*/
    pinmode(ledPin, OUTPUT);
}

void loop()
{
    ArduinoOTA.handle();

    /*Make the led blink*/
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
}
