/*include the librarys*/
#include "I2CTransfer.h"

/*make the structures for char and float*/
I2CTransfer myTransfer;

struct STRUCT
{
    char    z;
    float   y;
}testStruct;

char arr[] = "INPUT DATA";

/*setup the serial communication*/
void setup()
{
    Serial.begin(115200);
    Wire.begin();

    myTransfer.begin(Wire);

    testStruct.z = '$';
    testStruct.y = 4.5;
}

/*setup the communication pt2*/
void loop()
{
    /*use this variable to keep track of how many
     *bytes we're stuffing in the transmit buffer.
     */
    uint16_t sendSize = 0;

    //////////////////Stuff buffer with struct////////////////////
    sendSize = myTransfer.txObj(testStruct, sendSize);

    //////////////////Stuff buffer with array/////////////////////
    sendSize = myTransfer.txObj(arr, sendSize);

    /////////////////////////Send buffer/////////////////////////
    myTransfer.sendData(sendSize);
    delay(500);
}
