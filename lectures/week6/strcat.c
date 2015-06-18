#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char s[16];
    s[0] = '\0';

    // Concatenate each `argv[i]` onto `s`
    int i;
    for (i = 1; i < argc; i++) {
        strcat(s, argv[i]);
        strcat(s, "!");
    }

    printf("%s\n", s);

    return 0;
}
