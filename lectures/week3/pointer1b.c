#include <stdio.h>

int main(int argc, char *argv[])
{
    char x = 21;
    printf("x                = %d\n", x);

    char *x_ptr = &x;
    printf("*x_ptr           = %d\n", *x_ptr);

    *x_ptr = 42;
    printf("*x_ptr  (after)  = %d\n\n", *x_ptr);

    printf("x       (after)  = %d\n", x);

    return 0;
}
