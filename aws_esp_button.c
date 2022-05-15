#include "ssid/pwsd.h"
#include <WiFiCLientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include <M5StickC.h>


/*define the color */
#define TFT_GREY 0x5AEB 

/*setup the button and the values*/
const int button = 37;
int last_value = 0;
int cur_value = 0;

/*the MQTT topics that this device should publish/subscribe*/
#define AWS_IOT_PUBLISH_TOPIC "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"

WiFiCLientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(256);

/*connect to the AWS*/
void connectAWS()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.println("Connecting to Wi-Fi");

    while(WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    /*configure WiFiClientSecure to use the AWS IoT device credentials*/
    net.setCACert(AWS_CERT_CA);
    net.setCertificate(AWS_CERT_CRT);
    net.setPrivateKey(AWS_CERT_PRIVATE);

    /*connect to the MQTT broker on the AWS endpoint we defined earlier*/
    client.begin(AWS_IOT_ENDPOINT, 8883, net);

    /*create a message handler*/
    client.onMessage(messageHandler);

    Serial.print("Connecting to AWS IOT");

    while(!client.connect(THINGNAME))
    {
        Serial.print(".");
        delay(100);
    }

    if(!client.connected())
    {
        Serial.println("AWS IoT Timeout!");
        return;
    }

    /*subscribe to a topic*/
    client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

    Serial.println("AWS IoT Connected");
    M5.Lcd.println("AWS IoT Connected");
}

/*publish message*/
void publishMessage()
{
    StaticJsonDocument<200> doc;
    doc["time"] = millis();
    doc["message"] = "Hello Server, shoot me a message!";
    char jsonBuffer[512];
    serializeJson(doc, jsonBuffer); /*print this to the client*/
    
    client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

/*handle the message*/
void messageHandler(String &topic, String &payload)
{
    Serial.println("incoming: " + topic + " - " + payload);

    StaticJsonDocument<200> doc;
    deserializeJson(doc, payload);
    const char* message = doc["message"];

    M5.Lcd.fillScreen(TFT_GREY);
    M5.Lcd.setCursor(0, 0, 2);
    M5.Lcd.setTextColor(TFT_BLUE);
    M5.Lcd.setTextFont(2);
    M5.Lcd.println(payload);
}

/*make the setup*/
void setup()
{
    pinMode(button, INPUT);

    M5.begin();
    M5.Lcd.setRotation(3);
    M5.Lcd.fillScreen(TFT_GREY);
    M5.Lcd.setCursor(0, 0, 2);
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Lcd.setTextSize(2);

    Serial.begin(9600);
    connectAWS;
}

/*make the loop*/
void loop()
{
    /*read the value of BUTTON*/
    cur_value = digitalRead(button);

    if(cur_value != last_value)
    {
        if(cur_value == 0)
        {
            Serial.println("Button pressed");
            publishMessage();
            Serial.println("Published");
        }
        else
        {
            Serial.println("Button Status: released");
            Serial.println("value: 1");
        }
        last_value = cur_value;
    }
    client.loop();
}