#include <stdio.h>

void my_func(int x);

int main(int argc, char *argv[])
{
    int x = 42;

    printf("before call x = %d\n", x);
    my_func(x);
    printf("after call  x = %d\n", x);

    return 0;
}

void my_func(int x)
{
    printf("\tbefore doubling x = %d\n", x);

    // Double x
    x *= 2;

    printf("\tafter doubling x  = %d\n", x);
}

