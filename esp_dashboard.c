#ifdef ESP32
#include <ESPmDNS.h>
#include <WiFi.h>

/*if the board isn't the ESP32*/
#else
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#endif 

#include "dashboard.h"

static const char* ssid = "Your SSID";
static const char* password = "Your password";

/*the dashboard and the server*/
Dashboard* dashboard;
AsyncWebServer server(80);

bool test = false;

/*begin with the setup*/
void setup()
{
    Serial.begin(115200);

    Serial.print("Connecting to WiFi...");
    WiFi.begin(ssid, password);

    while(WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }
    
    Serial.println("Done.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    #ifdef ESP32
        WiFi.setSleep(false);
    #endif

    /*setup the mDNS responder
     *domain name
     *send IP addresses
     */
    if(MDNS.begin("dashboard"))
    {
        /*add service to MDNS-SD*/
        MDNS.addSerivce("http", "tcp", 80);
        Serial.println("mDNS responder started");
    }
    else
    {
        Serial.println("Error setting up MDNS responder!");
    }

    Serial.println("Starting server...");
    dashboard = new Dashboard(&server);

    dashboard->Add<uint32_t>("Uptime", millis, 5000);
    dashboard->Add("Bool", test, 2000);
    dashboard->Add<float>
    (
        "Float", []() {return millis() * 1.1;}, 2000);
    server.begin();
    Serial.println("Startet server.");
}

void loop()
{
    delay(10 * 1000);

    #ifdef ESP32
        /*this is a work around*/
        if(!MDNS.begin("dashboard"))
        {
            Serial.println("Error refreshing MDNS responder!");
        }
    #else
        MDNS.update();
    #endif

    #ifdef ESP32
        if(millis() - dashboard->last_used() < 30 * 1000)
        {
            WiFi.setSleep(false);
        }
        else
        {
            WiFi.setSleep(true);
        }
    #endif

    test = !test;
}


