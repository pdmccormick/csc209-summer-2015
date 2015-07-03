#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("%d + %d = %d\n", -3, 5, 2);

    printf("Hello %s!\n", "CSC209");

    printf("pi ~ %f\n", 3.14f);

    printf("C%cC209\n", 'S');

    printf("100%%!\n");


    /* Padded left with spaces */
    printf("|%5d|\n", 100);

    /* Padded left with 0's */
    printf("|%05d|\n", 200);

    /* Padded right with spaces */
    printf("|%-5d|\n", 300);

    return 0;
}

