#include <stdio.h>

void print_info(int i, int course_codes[], int num_enrolled[]);

int main(int argc, char *argv[])
{
    int i;
    int course_codes[2] = { 207, 209 };
    int num_enrolled[2] = { 100, 75 };

    for (i = 0; i < 2; i++) {
        print_info(i, course_codes, num_enrolled);
    }

    return 0;
}

void print_info(int i, int course_codes[], int num_enrolled[])
{
    printf("CSC%d has %3d students enrolled\n", course_codes[i], num_enrolled[i]);
}
