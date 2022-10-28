/*include the header file*/
#include <stdio.h>

/*main function*/
int main()
{
    int num[] = {10, 2, 15, 20, 34, 56, 86};
    int value, pos -1, i;

    /*get the input from the user*/
    printf("Enter the value to search: ");
    scanf("%d", &value);

    /*search the value in the array*/
    for(i = 0; i < 7; i++)
    {
        if(num[i] == value)
        {
            pos = i + 1;
            break;
        }
    }

    /*print the result*/
    if(pos == -1)
    {
        /*if the value is not found*/
        printf("Value not found in the array");
    }
    else
    {
        /*if the value is found*/
        printf("Value found at position %d", pos);
    }
}