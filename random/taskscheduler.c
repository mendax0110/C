///////////////////////////////////////////////////////////////////////////////
/////////////////////////SIMPLE TASK SCHEDULER IN C////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/*include the librarys*/
#include "TaskScheduler.hpp"

/*keep your code in the barcallbacks, but keep it small.
 *do not calll delay(), this doesnt word.
 */
void foo(void)
{
    Serial.println("foo is running!");
}

void bar(void)
{
    Serial.println("bar is running!");
}

/*define time constants for code clarity*/
constexpr uint16_t loopPreiodMsec = 500;
constexpr uint16_t fooPeriodMsec  = 1000;
constexpr uint16_t barPeriodMsec  = 2000;

/*define the task scheduler*/
void setup()
{
    Serial.begin(9600);
    delay(500);
    Serial.println("\nStarting TaskScheduler demo!");
}

/*create a task scheduler object*/
void loop()
{
    /*use the task scheduler*/
    taskloop();
    /*equivalent code to run handlers at the same period from
     *the main loop without the TS class.
     */
}

/*instantiate the task scheduler*/
void taskloop()
{
    /*notice the "static" keyword is needed in the declaration
     *these 2 declarations are sufficent to start running the
     *callbacks at their specified period automatically.
     */
    static taskScheduler fooLoop(fooPeriodMsec, foo);
    static taskScheduler barLoop(barPeriodMsec, bar);

    /*taskscheduler exposes the nowUsec global so we can use it*/
    Serial.print(nowUsec/1000);
    Serial.println("ms");

    delay(loopPeriodMsec);
}

/*convert periods to loop interations to use a simple counter*/
constexpr uint16_t fooIter = fooPeriodMsec/loopPeriodMsec;
constexpr uint16_t barIter = barPeriodMsec/loopPeriodMsec;

/*use a simple counter to run the callbacks at the specified period*/
void manualLoop()
{
    static uint32_t i = 0;
    i++;
    if(i % fooIter == 0) 
        {foo();}
    if(i % barIter == 0)
        {bar();}
    
    Serial.print(millis());
    Serial.println("ms");

    delay(loopPeriodMsec);
}
