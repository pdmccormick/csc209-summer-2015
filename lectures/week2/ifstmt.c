#include <stdio.h>

int main(int argc, char *argv[])
{
    if (1 > 100) {
        printf("1. You'll NEVER see this\n");
    }

    if (1 < 100) {
        printf("2. You'll always see this\n");
    }

    return 0;
}

