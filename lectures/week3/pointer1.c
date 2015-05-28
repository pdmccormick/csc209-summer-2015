#include <stdio.h>

int main(int argc, char *argv[])
{
    char x;
    unsigned long addr_x = (unsigned long) &x;

    x = 21;
    printf("x                = %d\n", x);
    printf("addr_x           = 0x%lx\n\n", (unsigned long) addr_x);

    /*
    printf("sizeof (x)       = %ld\n", sizeof (x));
    printf("sizeof (addr_x)  = %ld\n", sizeof (addr_x));
    */

    return 0;
}
