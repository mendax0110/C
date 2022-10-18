/*include the header file*/
#include <stdio.h>

/*swap the numbers*/
void swapnum(int var1, var2)
{
    int tempnum;

    /*copying var1 value into temp variable*/
    var1 = var2;

    /*copying temp variable value into var2*/
    var2 = tempnum;
}

/*main function*/
int main()
{
    int num1 = 35, num2 = 45;

    /*print the numbers before swap*/
    printf("Numbers before swap: %d %d", num1, num2);

    /*calling the swap function*/
    swapnum(num1, num2);

    /*print the numbers after swap*/
    printf("Numbers after swap: %d %d", num1, num2);
}