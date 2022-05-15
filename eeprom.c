#include <stdio.h>
#include <avr/io.h>
#include <avr/eeprom.h>

#include "serial.h"

/*write and read form and to the eeprom*/
int main(void)
{
    initalizeSerial();
    char buf[32];

    /*send the data to the eeprom*/
    char byteOfData = 0x12;
    sprintf(buf, "initialized: %d\r\n", byteOfData);
    serialWriteString(buf);

    /*read the data from the eeprom*/
    unsigned char* eepromAddress = 0x00;
    byteofData = eeprom_read_byte(eepromAddress);

    sprintf(buf, "after read: %d\r\n", byteOfData);
    serialWriteString(buf);

    /*RW*/
    byteOfData++;
    eeprom_write_byte(eepromAddress, byteofData);
    byteOfData = eeprom_read_byte(eepromAddress);

    sprintf(buf, "after write: %d\r\n", byteOfData);
    serialWriteString(buf);
}

