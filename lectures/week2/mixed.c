#include <stdio.h>

int main(int argc, char *argv[])
{
    /* int / int = int */
    double m = 5 / 6;
    printf("Result of 5/6 is %f\n", m);

    /* double / int = double */
    double n = (double)5 / 6;
    printf("Result of (double)5/6 is %f\n", n);

    /* double / int = double */
    double o = 5.0 / 6;
    printf("Result of 5.0/6 is %f\n", o);

    /* double / int = double but then converted to int */
    int p = 5.0 / 6;
    printf("Result of 5.0/6 is %d\n", p);

    return 0;
}

