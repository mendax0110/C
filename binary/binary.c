/*include the libraries*/
#include <stdio.h>
#include <math.h>

/*function to binary to octal*/
int binaryTooctal(int binaryNumber);
{
    int octalNumber = 0, decimalNumber = 0, i = 0;

    while(binaryNumber != 0)
    {
        decimalNumber += (binaryNumber%10) * pow(2,i);
        ++i;
        binaryNumber/=10;
    }

    i = 1;

    while (decimalNumber != 0)
    {
        octalNumber += (decimalNumber % 8) * i;
        decimalNumber /= 8;
        i *= 10;
    }

    return octalNumber;
}

/*get user input, call the function and print the result*/	
int main()
{
    int binaryNumber;

    printf("Enter a binary number: ");
    scanf("%d", &binaryNumber);

    printf("%d in binary = %d in octal", binaryNumber, binaryTooctal(binaryNumber));

    return 0;
}