/*include the header files*/
#include <stdio.h>
#include <avr/io.h>
#include <avr/eeprom.h>
#include "serial.h"

/*write and read from and to the eeprom*/
int main()
{
    initalizeSerial();
    char buf[32];

    /*send the data to the eeprom*/
    char byteOfData = 0x12;
    /*print the data to the serial monitor*/
    sprintf(buf, "initialized: %d\r\n", byteOfData);
    serialWriteString(buf);

    /*read the data from the eeprom*/
    unsigned char* eepromAddress = 0x00;
    byteOfData = eeprom_read_byte(eepromAddress);

    /*print the data to the serial monitor*/
    sprintf(buf, "after read: %d\r\n", byteOfData);
    serialWriteString(buf);

    /*write the data to the eeprom*/
    byteOfData++;
    eeprom_write_byte(eepromAddress, byteOfData);
    byteOfData = eeprom_read_byte(eepromAddress);

    /*print the data to the serial monitor*/
    sprintf(buf, "after write: %d\r\n", byteOfData);
    serialWriteString(buf);

    return 0;
}