#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cpufreq.h>

#ifndef LOG
#define LOG(...) printf(__VA_ARGS__);
#endif

/*define the CPUINDEX*/
#define CPU_INDEX 0

int setCPUMax(unsigned int index)
{
    unsigned long cpu_cur = 0;
    unsigned long cpu_max = 0;
    unsigned long cpu_min = 0;

    /*Check the cpu index*/
    if(cpufreq_cpu_exists(index) != 0)
    {
        LOG("Invalid CPU index!\n");
        return -1;
    }

    /*Check the hardware limits*/
    if(cpufreq_get_hardware_limits(index, &cpu_min, &cpu_max) != 0)
    {
        LOG("Unable to get hardware limits!\n");
        return -1;
    }

    /*try to set the frequency*/
    if(cpufreq_set_frequency(index, cpu_max) != 0)
    {
        LOG("Unable to set frequency(%luMHz) Are u root?\n", cpu_max / 1000);
        return -1;
    }

    cpu_cur = (cpufreq_get_freq_kernel(index) / 1000);

    LOG("Current CPU Frequency: %lu MHz\n", cpu_cur);

    return 0;
}

/*main part of the program to set the frequency of the cpu min and max*/
int main()
{
    setCPUMin(CPU_INDEX);
    setCPUMax(CPU_INDEX);

}