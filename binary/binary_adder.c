/*include the librarys*/
#include <stdio.h>

/*get bit 1 of 1.
 *returns are either 0 or 1
 */
int getBits(int a, int i)
{
    return((a & (1 << i)) >> i);
}

/*add bits a and b,
 *taking into account the carry.
 */
int sum(carry_in, a, b)
{
    return((carry_in ^ a) ^ b);
}

/*figures out what the carry-over is*/
int carry(carry_in, a, b)
{
    return(carry_in & a) & b;
}

/*set bit i of result to be s, either 0 or 1*/
int setBit(result, i, s)
{
    if(s == 1)
        return result | (1 << i);
    return result & ~(1 << i);
}

int main()
{
    unsigned int x, y;
    scanf("%d %d", &x, &y);

    unsigned int result     = 0;
    unsigned int carry_in   = 0;

    unsigned int i = 0;
    unsigned int a = 0;
    unsigned int b = 0;

    for(i = 0; i < 32; i++) /*you probably can't use the increment op*/
    {
        a = getBit(x, i);
        b = getBit(y, i);

        unsigned int s = sum(carry_in, a, b);
        unsigned int carry_out = carry(carry_in, a, b);

        result = setBit(result, i, s);
        carry_in = carry_out;
    }

    if(carry_in > 0)
        printf("\n overflow has occured, result incorrect\n");
    printf("%#x %d\n", result, result);

    return 0;                                
}