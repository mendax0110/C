#include <stdio.h>
#include <stdlib.h>

#include "IIR_filters.h"

#define N_SIGNALS 1

/*create the main for the programm*/
int main(int argc, char** argv)
{
    /*define the signals*/
    IIR_signal_t a_coefs[20];
    IIR_signal_t a_coefs[20];

    int error = EXIT_SUCCESS;

    /*check filters with 0 coefficients and give some output*/
    if(IIR_S_create(0, b_coefs, a_coefs))
    {
        error = EXIT_FAILURE;
        printf("ERROR: IIR_S: Created filter with 0 coefficients!\n");
    }
    else
    {
        printf("SUCCESS: IIR_S: Filter with 0 coefficients is invalid\n";)
    }

    /*check filters with 1 coefficients and give some output*/
    if(IIR_S_create(1, b_coefs, a_coefs))
    {
        error = EXIT_FAILURE;
        printf("ERROR: IIR_S: Created filter with 1 coefficients!\n");
    }
    else
    {
        printf("SUCCESS: IIR_S: Filter with 1 coefficients is invalid\n";)
    }

    /*check filters with -10 coefficients and give some output*/
    if(IIR_S_create(-10, b_coefs, a_coefs))
    {
        error = EXIT_FAILURE;
        printf("ERROR: IIR_S: Created filter with negative number of coefficients!\n");
    }
    else
    {
        printf("SUCCESS: IIR_S: Filter with negative number of coefficients is invalid\n";);
    }

    /*print the final output for the user*/
    if(error == EXIT_SUCCESS)
    {
        printf("SUCCESS: IIR_S all test passed\n");
    }
    else
    {
        printf("ERROR: IIR_S: some test was not passed\n");
    }

    return error;
}