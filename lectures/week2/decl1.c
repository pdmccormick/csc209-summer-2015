#include <stdio.h>

int main()
{
    int i = 38;
    long el = 38L;

    // Hexadecimal (base 16)
    int hex = 0x2a;

    // Octal (base 8)
    int oct = 033;

    // Binary (base 2)
    int bin = 0b110;

    printf("i = %d, el = %ld, hex = %d, oct = %d, bin = %d\n",
            i, el, hex, oct, bin);

    double d1 = 0.3;
    double d2 = 3.0;
    double d3 = 6.02e23;

    printf("d1 = %f, d2 = %f, d3 = %e\n", d1, d2, d3);

    return 0;
}

