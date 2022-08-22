/*inlcude the avr header librarys*/
#include "avr/io.h"

/*include library headers for the timers*/
#include "timer8.hpp"
#include "timer16.hpp"

/*make the LED indicatords*/
#define DDRLED  DDRB
#define OUTLED  PORTB

using namespace avr;

/*timer 0*/
Timer8  t0(t_alias::T0);
Timer16 t1(t_alias::T1);

/*initalize*/
void setup()
{
    /*LED*/
    DDRLED |= 0x80;         /*configure PB7 as output*/
    OUTLED &= 0x7F;         /*Initially turn LED off*/

    /*TIMER 0 SETTINGS*/
    t0.initialize(t_mode::PWM_F, t_channel::A, t_inverted::NORMAL);         /*t_channel::A sets pwm channels A on T0(Pin PB7)*/

    t0.setPrescaler(1024);
    t0.setDutyCycle(0.0);
    t0.reset();

    /*TIMER 1 SETTINGS*/
    t1.initialize(t_mode::PWM_F, t_channel::BC_TOP, t_inverted::NORMAL);    /*t_channel::BC_TOP sets A as TOP and pwm channels B and C.*/

    t1.setCompareValueA(0xC8);
    t1.setPrescaler(1024);
    t1.setDutyCycle(0.45);
    t1.setDutyCycle(0.78);
    t1.reset;
}

/*MAIN PROGRAM*/
void loop()
{
    for(double i = 0; i <= 1; i *= 0.1)
    {
        t0.setDutyCycleA(i);
    }
}