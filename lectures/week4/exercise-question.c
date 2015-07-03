#include <stdio.h>

int main()
{
    long i = 2;
    long j = 209;
    long k;

    long a[4] = { 1, 2, 3, 4 };

    long *p;
    long *q;

    p = &i;
    j = *p;
    *p = 1;
    q = &a[j];

    a[0] = 11;
    a[3] = 12;
    a[i] = 13;
    a[j] = 14;
    q[0] = 15;
    q[1] = 16;

    if (1) {
        printf("&i    = %p\n", &i);
        printf("&j    = %p\n", &j);
        printf("p     = %p\n", p);
        printf("q     = %p\n", q);
        printf("\n");

        printf("&a    = %p\n", &a);
        printf("&a[0] = %p\n", &a[0]);
        printf("&a[1] = %p\n", &a[1]);
        printf("&a[2] = %p\n", &a[2]);
        printf("&a[3] = %p\n", &a[3]);
        printf("\n");

        printf("i    = %ld\n", i);
        printf("j    = %ld\n", j);
        printf("a[0] = %ld\n", a[0]);
        printf("a[1] = %ld\n", a[1]);
        printf("a[2] = %ld\n", a[2]);
        printf("a[3] = %ld\n", a[3]);
    }

    // Suppress unused variable warnings
    (void)k;

    return 0;
}
