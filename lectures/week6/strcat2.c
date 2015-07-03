#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int i;
    size_t len = 0;

    // Add up all string lengths
    for (i = 1; i < argc; i++) {
        len += strlen(argv[i]);
        // Add +1 for each '!'
        len++;
    }

    // Another +1 for the NUL terminator
    char *s = (char *) malloc(len + 1);

    if (!s) {
        perror("malloc");
        return -1;
    }

    s[0] = '\0';

    // Concatenate each `argv[i]` onto `s`
    for (i = 1; i < argc; i++) {
        strcat(s, argv[i]);
        strcat(s, "!");
    }

    printf("%s\n", s);

    return 0;
}
