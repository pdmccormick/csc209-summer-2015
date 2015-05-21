#include <stdio.h>

int main()
{
    int a = -1;
    unsigned int b = -1;
    
    printf("a = %d\n", a);
    printf("signed b         = %d\n", b);
    printf("unsigned b       = %u\n", b);
    printf("unsigned (b + 1) = %u\n", b + 1);

    return 0;
}

