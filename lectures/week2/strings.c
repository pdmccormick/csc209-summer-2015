#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;
    char course[] = "CSC209";

    printf("Course: %s\n", course);

    printf("Let's print 6 characters from the string:\n");

    for (i = 0; i < 6; i++) {
        printf("course[%d] -> '%c' (%d)\n", i, course[i], course[i]);
    }

    printf("\nCan we risk a 7th?\n");
    i = 7;
    printf("course[%d] -> '%c' (%d)\n", i, course[i], course[i]);

    printf("\nHow about an 8th?\n");
    i = 8;
    printf("course[%d] -> '%c' (%d)\n", i, course[i], course[i]);

    printf("\nHow about we risk adding a letter?\n");
    course[6] = 'H';
    course[7] = '\0';
    printf("Updated string: %s\n", course);

    printf("\nCould we get away with adding one more?\n");
    course[7] = '1';
    course[8] = '\0';
    printf("Updated string: %s\n", course);

    printf("\nHey, we are getting away with this, let's just go for it!\n");
    course[8] = 'Y';
    course[9] = '\0';
    printf("Updated string: %s\n", course);

    printf("\nWow, I survived... I AM INVINCIBLE!!!\n");

    return 0;
}

