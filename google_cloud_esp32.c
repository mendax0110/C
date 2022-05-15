#include <client.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <MQTT.h>
#include <CloudIoTCore.h>
#include <CloudIoTCoreMqtt.h>
/*update this library with your informations*/
#include "ciotc_config.h"

/*the MQTT callback function for commands and configurations updates*/
void messageReceived(String &topic, String &payload)
{
    Serial.println("incoming: " + topic + " - " + payload);
}

/*initialize WiFi and MQTT for this board*/
Client *netClient;
CloudIoTCoreDevice *device;
CloudIoTCoreMqtt *mqtt;
MQTTClient *mqttClient;
unsigned long iat = 0;
String jwt;

/*helpers specific to this board*/
String getDefaultSensor()
{
    return "Wifi: " + String(WiFi.RSSI()) + "db";
}

String getJwt()
{
    iat = time(nullptr);
    Serial.println("Refreshing JWT");
    jwt = device->createJWT(iat, jwt_exp_secs);
    return jwt;
}

/*setup the wifi*/
void setupWifi()
{
    Serial.println("Starting wifi");

    WiFi.mode(WIFI_STA);
    /*WiFi.setSleep(false); /*this may help with disconnects?*/
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
    }

    configTime(0, 0, ntp_primary, ntp_secondary);
    Serial.println("Waiting on time sync....");
    while (time(nullptr) < 1510644967)
    {
        delay(10);
    }
}

/*connect to the wifi*/
void connectWifi()
{
    Serial.print("checking wifi...");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }
}

/*orchestrates various methods from preceeding code*/
bool publishTelemetry(String data)
{
    return mgtt->publishTelemetry(data);
}

bool publishTelemetry(const char *data, int length)
{
    return mqtt->publishTelemetry(data, length);
}

bool publishTelemetry(String subfolder, String data)
{
    return mqtt->publishTelemetry(subfolder, data);
}

bool publishTelemetry(String subfolder, const char *data, int length)
{
    return mqtt->publishTelemetry(subfolder, data, length);
}

void connnect()
{
    connectWifi();
    mqtt->mqttConnect();
}

/*setup the cloud iot connection*/
void setupCloudIoT()
{
    device = new CloudIoTCoreDevice(
        project_id, location, registry_id,
        device_id, private_key_str
    );

    setupWifi();
    netClient   = new WiFiClientSecure();
    mqttClient  = new MQTTClient(512);
    mqttClient->setOptions(180, true, 1000); /*keep this alive, clean this session and then timeout*/
    mqtt = new CloudIoTCoreMqtt(mqttClient, netClient, device);
    mqtt->setUseLts(true);
    mqtt->startMQTT();
}
