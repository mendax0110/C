#include <stdio.h>
void swapnum(int var1, int var2)
{
    int tempnum;
    /*copying var1 value into temp variable*/
    tempnum = var1;

    /*copying var2 value into var1*/
    var1 = var2;

    /*copying temp variable value into var2*/
    var2 = tempnum;
}
int main()
{
    int num1 = 35, num2 = 45;
    printf("Before swapping: %d, %d", num1, num2);

    /*calling swap function*/
    swapnum(num1, num2);
    printf("\nAfter swapping: &d, %d", num1, num2);
}

