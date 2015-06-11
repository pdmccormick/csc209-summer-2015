#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;

int main(int argc, char *argv[])
{
    byte *binary_data = (byte *) malloc(1024);

    if (!binary_data) {
        return -1;
    }

    // Can't as easily do this accidentally. Compiler will at least complain
    // with a warning that you should think about carefully: `binary_data` is
    // not supposed to be thought of as a C style, NUL terminated string!
    char *str = strdup(binary_data);

    free(str);

    free(binary_data);

    return 0;
}
