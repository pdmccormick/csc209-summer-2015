#include <stdio.h>

int main(int argc, char *argv[])
{
    long var = 100;

    printf("var            = %ld\n", var);
    printf("address-of-var = 0x%lx\n", (long) &var);

    return 0;
}

