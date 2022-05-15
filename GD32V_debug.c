/*first of all, this is a simple and small debug print. Pretty useful on embedded
 *part where the kilobytes matter.
 */
#include <stdarg.h>

/*put the hexadecimal*/
static void puthex(unsigned char c)
{
    static char hex[] = "0123456789adcdef";
    putc(hex[(c >> 4)]);
    putc(hex[c & 0xf]);
}

static puthexi(int i)
{
    puthex(i >> 24);
    puthex(i >> 16);
    puthex(i >> 8);
    puthex(i);
}

#if 0

puthex(long l)
{
    puthexi(l >> 32);
    puthexi(l & 0xffffffff);
}

#endif

/*TODO: decide if recursion is resonable in out tiny interrupt stack*/
putdec(ind d)
{
    if(d < 0)
    {
        putc('-');
        d = -d;
    }
    
    if(d >= 10)
    {
        print_i(d / 10);
    }
    putc(d % 10 + '0');
}

