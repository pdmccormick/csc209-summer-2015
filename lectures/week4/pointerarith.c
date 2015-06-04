#include <stdio.h>

int main(int argc, char *argv[])
{
    // Don't even think of dereferencing these pointers...
    char *p = (char *) 0x1000;
    short *q = (short *) 0x2000;
    int *r = (int *) 0x4000;
    long *s = (long *) 0x8000;

    printf("p     = %p\n", p);
    printf("p + 1 = %p\n", p + 1);
    printf("p + 2 = %p\n", p + 2);
    printf("p + 3 = %p\n", p + 3);
    printf("p + 4 = %p\n", p + 4);
    printf("\n");

    printf("q     = %p\n", q);
    printf("q + 1 = %p\n", q + 1);
    printf("q + 2 = %p\n", q + 2);
    printf("q + 3 = %p\n", q + 3);
    printf("q + 4 = %p\n", q + 4);
    printf("\n");

    printf("r     = %p\n", r);
    printf("r + 1 = %p\n", r + 1);
    printf("r + 2 = %p\n", r + 2);
    printf("r + 3 = %p\n", r + 3);
    printf("r + 4 = %p\n", r + 4);
    printf("\n");

    printf("s     = %p\n", s);
    printf("s + 1 = %p\n", s + 1);
    printf("s + 2 = %p\n", s + 2);
    printf("s + 3 = %p\n", s + 3);
    printf("s + 4 = %p\n", s + 4);
    printf("\n");

    return 0;
}
