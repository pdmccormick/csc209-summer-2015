#include <stdio.h>

int main(int argc, char *argv[])
{
    long array[4] = { 100, 200, 300, 400 };

    printf("array[0]     = %ld\n", array[0]);
    printf("array[1]     = %ld\n", array[1]);
    printf("array[2]     = %ld\n", array[2]);
    printf("array[3]     = %ld\n", array[3]);
    printf("\n");

    printf("&array       = 0x%lx\n", (unsigned long) &array);
    printf("&array[0]    = 0x%lx\n", (unsigned long) &array[0]);
    printf("&array[1]    = 0x%lx\n", (unsigned long) &array[1]);
    printf("&array[2]    = 0x%lx\n", (unsigned long) &array[2]);
    printf("&array[3]    = 0x%lx\n", (unsigned long) &array[3]);
    printf("\n");

    /*
    long *array_ptr = (long *) &array;
    printf("&array       = 0x%lx\n", (unsigned long) &array);
    printf("array_ptr    = 0x%lx\n\n", (unsigned long) array_ptr);
    */

    //printf("*array_ptr   = %ld\n", *array_ptr);

    return 0;
}
