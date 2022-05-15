/*include the librarys
 *you must set the devide id, device key and IoT Hub name suffix
 */
#include "iot_configs.h"
#include <AzureIoTProtocol_MGTT.h>

/*define the HTTP and MQTT*/
#if defined(IOT_CONFIG_MQTT)
    #include <AzureIoTProtocol_MQTT.h>
#elif defined(IOT_CONFIG_HTTP)
    #include <AzureIoTProtocol_HTTP.h>
#endif

#include "sample.h"
#include "esp8266/sample_init.h"


/*setup the SSID and password*/
static char ssid[] = IOT_CONFIG_WIFI_SSID;
static char pass[] = IOT_CONFIG_WIFI_PASSWORD;

/*initialize the ssid and password*/
void setup()
{
    sample_init(ssid, pass);
}

/*azure IoT samples conatain their own loops, so only run them once*/
static bool done = false;

void loop()
{
    if(!done)
    {
        /*run this sample
         *you must set the device id, device key and IoT hub name and IoT suffix*/
         *iot configs h 
         */
        sample_run();
        done = true;
    }
    else
    {
        delay(500);
    }
}


