#include <stdio.h>
#include <math.h>

int binaryTooctal(long binarynum)
{
    int octalnum = 0, decimalnum = 0, i = 0;

    while(binarynum != 0)
    {
        decimalnum = decimalnum + (binarynum%10) * pow(2,i);
        i++;
        binarynum = binarynum / 10;
    }

    i = 1;

    while(decimalnum != 0)
    {
        octalnum = octalnum + (decimalnum%8) * i;
        decimalnum = decimalnum / 8;
        i = i * 10;
    }

    return octalnum;
}
int main()
{
    long binarynum;

    printf("Enter a binary number: ");
    scanf("%ld", &binarynum);

    printf("Equivalent octal value: %d", binaryTooctal(binarynum));

    return 0;
}
