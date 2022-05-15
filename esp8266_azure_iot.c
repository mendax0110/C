#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"

/*setup the wifi settings*/
const char* ssid = "YourSSID";
const char* password = "SSIDPSWD";

/*define the pin connected to the DHT Sensor*/
#define DHTPIN 2 

/*Azure IoT Hub Connection Settings*/
const String AzureIoTHubURI = "https://{iothubname}.azure-devices.net/devices/{id}/messages/events?api-version=2020-03-13";
/*openssl s_client -servername myioteventhub.azure-devices.net -connect myioteventhub.azure-devices.ne:443 | openssl x509 -fingerprint --noout*/
const String AzureIoTHubFingerPrint ="{YourGeneratedFingerPrint}";
/*azure iot hub generates-sas-token --device-id {YourIoTDeviceID} --hub-name{YourIoTHubName}*/
const String AzureIoTHubAuth = "{SAS Token}";

/*define your DHT Type here*/
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(115200);
    Serial.println(F("DHTxx test!"));

    dht.begin();
    /*init serial line, serial begin(115200)*/
    Serial.println("ESP8266 starting in normal mode");

    /*connecting to WiFi*/
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");

    /*Print the IP address*/
    Serial.println(WiFi.localIP());
}

void loop()
{
    /*wait a few seconds between measurements*/
    delay(5000);
    float h = dht.readHumidity();
    /*read the temperature as Celsius(the default)*/
    float t = dht.readTemperature();
    /*read temperature as Fahrenheit (isFahrenheit = ture)*/
    float f = dht.readTemperature(true);

    /*check if any reads failed and exit early (to try again)*/
    if(isnan(h) || isnan(t) || isnan(f))
    {
        Serial.prinln(F("Failed to read from DHT sensor!"));
        return;
    }

    /*compute heat index in Fahrenheit(the default)*/
    float hif = dht.computeHeatIndex(f, h);
    /*compute heat index in Celsius(isFahrenheit = false)*/
    float hic = dht.computeHeatIndex(t, h, true);

    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F("% Temperature: "));
    Serial.print(t);
    Serial.print(F("°C "));
    Serial.print(f);
    Serial.print(F("°F Heat Index: "));
    Serial.print(hic);
    Serial.print(F("°C "));
    Serial.print(hif);
    Serial.print(F("°F"));
    
    String PostData = "{\"DeviceId\":\"ESP8266-0001\",\"Temperature\":"+String(t)+",\"Humidity\":"+String(h)+"}";
        Serial.println(PostData);
        /*send data to the cloud(azure M$)*/
        int returnCode = RestPostData(AzureIoTHubURI,AzureIoTHubFingerPrint,AzureIoTHubAuth,PostData);
        Serial.println(returnCode);
}

/*make the functions*/
int RestPostData(String URI, String figerprint, String Authorization, String PostData)
{
    HTTPClient http;
    http.begin(URI,figerprint);
    http.addHeader("Authorization",Authorization);
    http.addHeader("Content-Type", "application/atom+xml;type=entry;charset=utf-8");

    int returnCode = http.POST(PostData);
    if(returnCode < 0)
    {
        Serial.prinln("RestPostData: Error sending data: "+String(http.errorToString(returnCode).c_str()));
    }
    http.end();

    return returnCode;
}

