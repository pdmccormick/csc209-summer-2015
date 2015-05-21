#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;
    char course[] = "CSC209";

    printf("Course: %s\n", course);

    for (i = 0; i < 6; i++) {
        printf("course[%d] -> %d\n", i, course[i]);
    }

    return 0;
}

