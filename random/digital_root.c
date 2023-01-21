/*include the libraries*/
#include <stdio.h>

/*main part of the program*/
int main()
{
    unsigned int number, temp, droot = 0;

    /*ask user to give a number*/
    printf("Enter a positive number: ");
    scanf("%u", &number);

    /*calculate digital root of the number*/
    temp = number;

    /*loop until temp is not equal to 0*/
    while(temp != 0)
    {
        int digit = temp % 10;
        droot += digit;
        temp /= 10;

        if(temp == 0 && droot > 9)
        {
            temp = droot;
            droot = 0;
        }
    }

    /*print digital root of the number*/
    printf("Digital root of %u is %d", number, droot);

    return 0;
}