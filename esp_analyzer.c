#include <c_types.h>

/*define your baudrate
 *check if it is same as in the processing
 */
#define baudrate 115200 

/*number of samples to collect*/
static const int N_SAMPLES = 300;

/*what pins to use, between 0 and 15*/
static const int PIN0 = 4;
static const int PIN1 = 5;
static const int PIN2 = 12;
static const int PIN3 = 14;

/*unused pins should be tied to the ground(PE)*/
static_assert(PIN0 >= 0 && PIN0 < 16, "");
static_assert(PIN1 >= 0 && PIN1 < 16, "");
static_assert(PIN2 >= 0 && PIN2 < 16, "");
static_assert(PIN3 >= 0 && PIN3 < 16, "");

static constexpr uint32_t MASK = (1 << PIN0) | (1 << PIN1) | (1 << PIN2) | (1 << PIN3);

/*setup the baudrate ant the serial connection*/
void setup()
{
    Serial.begin(baudrate);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    pinMode(PIN0, INPUT_PULLUP);
    pinMode(PIN1, INPUT_PULLUP);
    pinMode(PIN2, INPUT_PULLUP);
    pinMode(PIN3, INPUT_PULLUP);
}

/*when did change happen*/
unsigned long times[N_SAMPLES];
/*GPI value at time*/
uint32_t values[N_SAMPLES];

extern void ICACHE_RAM_ATTR collect()
{
    times[0] = micros();
    vlaues[0] = GPI & MASK;
    for(int i = 1; i < N_SAMPLES; ++i)
    {
        uint32_t values;
        do
        {
            values = GPI & MASK;
        } 
        while(value == value[i - 1]);
        times[i] = micros();
        values[i] = value;
    }
}

int compactValue(uint32_t value)
{
    int res = 0;
    if((value & (1 << PIN0)) != 0)
    {
        res |= (1 << 0);
    }
    if((value & (1 << PIN0)) != 0)
    {
        res |= (1 << 1);
    }
    if((value & (1 << PIN0)) != 0)
    {
        res |= (1 << 2);
    }
    if((value & (1 << PIN0)) != 0)
    {
        res |= (1 << 3);
    }
    return res;
}

void report()
{
    Serial.println("S");
    Serial.print(compactValue(values[0]));
    Serial.print(":");
    Serial.println(N_SAMPLES - 1);

    for(int i = 1; i < N_SAMPLES; ++i)
    {
        Serial.print(compactValue(values[i] ^ values[i - 1]));
        Serial.print(":");
        Serial.println(times[i] - times[0]);
    }
}

void loop()
{
    while(Serial.read() != 'G')
    {
        delay(1);
    }

    digitalWrite(LED_BUILTIN, LOW);
    ESP.wdtDisable();
    collect();
    ESP.wdtEnable(WDTO_8S);
    digitalWrite(LED_BUILTIN, HIGH);
    report();
}
