#include <stdio.h>

int main(int argc, char *argv[])
{
    int always_false = 0;
    int always_true = 209;

    if (always_false) {
        printf("1. You'll NEVER see this\n");
    }

    if (!always_false) {
        printf("2. (!false) is true\n");
    }

    if (always_true) {
        printf("3. You'll always see this\n");
    }

    if (!always_true) {
        printf("4. You'll NEVER see this\n");
    }

    return 0;
}

