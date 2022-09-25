/*include the header files*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/*main function*/
int main()
{
    char ch;
    float voltage, current, resistance, result;

    /*display the menu*/
    printf("OHM's Law Calculator\n");
    printf("Choose from the following options:\n");
    printf("1. calculate Voltage\n");
    printf("2. calculate Current\n");
    printf("3. calculate Resistance\n");
    printf("4. Exit\n");

    /*get the user's choice*/
    scanf("%c", &ch);

    switch(ch)
    {
        /*calculate voltage*/
        case '1':
            printf("Enter the current and resistance: ");
            scanf("%f %f", &current, &resistance);
            result = current * resistance;
            printf("The voltage is %f volt\n", result);
            break;

        /*calculate current*/
        case '2':
            printf("Enter the voltage and resistance: ");
            scanf("%f %f", &voltage, &resistance);
            result = voltage / resistance;
            printf("The current is %f ampere\n", result);
            break;

        /*calculate resistance*/
        case '3':
            printf("Enter the voltage and current: ");
            scanf("%f %f", &voltage, &current);
            result = voltage / current;
            printf("The resistance is %f ohm\n", result);
            break;

        /*exit*/
        default:
            printf("Invalid choice\n");
            break;

            exit(0);
    }
    return 0;
}