/*include the header file*/
#include <stdio.h>

/*main function of the program*/
int main()
{
    int var;
    int *ptr;
    int **pptr;

    /*actual variable declaration*/
    var = 3000;

    /*take the address of var*/
    ptr = &var;

    /*take the address of ptr using address of operator &*/
    pptr = &ptr;

    /*print var*/
    printf("Value of var = %d\n", var);

    /*print the address of var*/
    printf("Value available at *ptr = %d\n", *ptr);

    /*print the address of ptr*/
    printf("Value available at **pptr = %d\n", **pptr);

    return 0;
}