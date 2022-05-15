/*include the librarys*/
#include <Ethernet.h>
#include <MQTT.h>

/*set the mac and the ip*/
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
byte ip[]  = {192, 168, 178, 40}; /*this can be changed to the right network*/

EthernetClient net;
MQTTClient client;

unsigned long lastMillis = 0;

/*print serial, connect client etc*/
void connect()
{
    Serial.print("connecting...");
    while(!client.connect("arduino", "public", "public"))
    {
        Serial.print(".");
        delay(1000);
    }

    Serial.println("/hello");
    /*client.unsubscribe("/hello")*/
}

/*receive message*/
void messageReceived(String &topic, String &payload)
{
    Serial.prinln("incoming: " + topic + " - " + payload);
}

/*publish it all*/
void setup()
{
    Serial.begin(115200);
    Ethernet.begin(mac, ip);

    /*local domain names( .local) are not supported
     *please set the IP Address direct.
     */
    client.begin("public.cloud.shiftr.io", net);
    client.onMessage(messageReceived);
    connect();
}

void loop()
{
    client.loop();

    if(!client.connected())
    {
        connect();
    }

    /*publish a message roughly every second*/
    if(millis() - lastMillis > 1000)
    {
        lastMillis = millis();
        client.publish("/OUTPUT", "MESSAGE");
    }
}

