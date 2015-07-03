#include <stdio.h>

int main(int argc, char *argv[])
{
    int true_value = 1 < 100;
    int false_value = 1 > 100;

    printf("true_value = %d\n", true_value);
    printf("false_value = %d\n", false_value);

    if (1 > 100) {
        printf("1. You'll NEVER see this\n");
    }

    if (1 < 100) {
        printf("2. You'll always see this\n");
    }

    return 0;
}

