#include <stdio.h>

int main(int argc, char *argv[])
{
    long var = 50;
    long array[4] = { 100, 200, 300, 400 };

    printf("var       = %ld\n", var);
    printf("array[0]  = %ld\n", array[0]);
    printf("array[1]  = %ld\n", array[1]);
    printf("array[2]  = %ld\n", array[2]);
    printf("array[3]  = %ld\n", array[3]);
    printf("\n");

    printf("&array    = 0x%lx\n", (long) &array);
    printf("&array[0] = 0x%lx\n", (long) &array[0]);
    printf("&array[1] = 0x%lx\n", (long) &array[1]);
    printf("&array[2] = 0x%lx\n", (long) &array[2]);
    printf("&array[3] = 0x%lx\n", (long) &array[3]);

    return 0;
}

