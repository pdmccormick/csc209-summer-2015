#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;
    int course_codes[2] = { 207, 209 };
    int num_enrolled[2] = { 100, 75 };

    for (i = 0; i < 2; i++) {
        printf("CSC%d has %d students enrolled\n", course_codes[i], num_enrolled[i]);
    }

    return 0;
}

