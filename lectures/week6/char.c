#include <stdio.h>

int main(int argc, char *argv[])
{
    if (1 == (unsigned char) 257) {
        printf("1 == (unsigned char) 257\n");
    }

    if ('A' == 65) {
        printf("'A' == 65\n");
    }

    return 0;
}
