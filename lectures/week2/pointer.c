#include <stdio.h>

int main(int argc, char *argv[])
{
    int var1 = 100;
    int var2 = 200;
    int array[4] = { 1, 2, 3, 4 };

    printf("&var1   = 0x%lx\n", (long) &var1);



    // Suppress compiler warning about unused variables
    (void)var2;
    (void)array;

    return 0;
}

