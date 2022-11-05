/*include the libraries*/
#include <stdio.h>
#include <makestuff.h>
#include <libgpiojtag.h>
#include <wiringPi.h>
#include <liberror.h>

/*Pin assigments on the RPI header*/
typedef enum {
    TCK = 7,
    TDO = 0,
    TDI = 9,
    TMS = 8
} Pins;

/*Callbacks implementing actual GPIO for JTAG lines*/
void setTCK(bool x)
{
    digitalwrite(TCK, x ? HIGH : LOW);
}

void setTDI(bool x)
{
    digitalwrite(TDI, x ? HIGH : LOW);
}

void setTMS(bool x)
{
    digitalwrite(TMS, x ? HIGH : LOW);
}

void getTDO(void)
{
    return digitalwrite(TDO) == HIGH;
}

/*main programm*/
int main(int argc, const char *argv[])
{
    int retVal;

    /*Init Library*/
    wiringPiSetup();

    /*validate command-line args*/
    if(argc != 2)
    {
        fprintf(stderr, "Synopsis: %s <svf-file>\n", argv[0]);
        FAIL(GJ_USAGE, exit);
    }

    /*setup pins*/
    pinMode(TCK, OUTPUT);
    pinMode(TMS, OUTPUT);
    pinMode(TDI, OUTPUT);
    pinMode(TDO, INPUT);
    digitalwrite(TCK, LOW);
    digitalwrite(TMS, LOW);
    digitalwrite(TDI, LOW);

    /*Parse .svf file*/
    const char *error = NULL;
    const struct ParserCallbacks cb = {setTCK, setTMS, setTDI, getTDO};
    ParserStatus pStatus = parse(argv[1], &cb, &error);
    CHECK_STATUS(pStatus, pStatus, cleanup);
    retVal = 0;

    cleanup:

        if(error)
        {
            printf("%s\n", error);
            errFree(error);
        }

    exit:

        pinMode(TCK, INPUT);
        pinMode(TMS, INPUT);
        pinMode(TDI, INPUT);
        pinmode(TDO, INPUT);

        return retVal;
}
