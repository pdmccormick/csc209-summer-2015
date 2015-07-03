#include <stdio.h>
#include <string.h>

char *get_course_code();

int main(int argc, char *argv[])
{
    char *str;

    str = get_course_code();
    printf("1) str = \"%s\"\n", str);

    // This will crash, because the string pointer points into the constant
    // (i.e. read-only) data region
    str[0]++;
    printf("2) str = \"%s\"\n", str);

    return 0;
}

char *get_course_code()
{
    char *str = "CSC209";

    // Comment out this return to avoid the crash
    return str;

    /* Use `strdup` to duplicate a string by first allocating memory (using
     * `malloc`), and then copying the old value into it. */
    return strdup(str);
}
