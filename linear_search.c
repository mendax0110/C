/*include the librarys*/
#include <stdio.h>

/*main part of the program*/
int main()
{
    int num[] = {10,2,15,20,34,56,86};
    int value,pos = -1,i;

    printf("Enter The value You can search: ");
    scanf("%d", &value);

    for(i = 0; i < 7; i++)
    {
        if(value==num[i])
        {
            pos = i+1;
            break;
        }
    }

    if(pos == -1)
        printf("Item is not found ");
    else
        printf("The Value is found at %d position. ",pos);
}