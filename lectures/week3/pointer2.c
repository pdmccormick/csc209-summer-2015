#include <stdio.h>

void add_21(int x);

int main(int argc, char *argv[])
{
    int x = 21;

    printf("main   BEFORE x = %d\n", x);

    add_21(x);

    printf("main   AFTER  x = %d\n", x);

    return 0;
}

void add_21(int x)
{
    // Add 21 to the parameter
    x += 21;
}



    //printf("             &x = 0x%lx\n", (unsigned long) &x);
