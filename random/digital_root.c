/*include the needed librarys*/
#include <stdio.h>

/*main part of the program*/
int main()
{
    unsigned int number, temp, droot = 0;

    printf("Enter a positive number: ");
    scanf("%u", &number);

    temp = number;

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

    printf("The digital root of %u is %u\n", number, droot);
    return 0;
}
