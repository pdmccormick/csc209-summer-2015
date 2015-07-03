#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *strdup209(const char *s)
{
    size_t len = strlen(s);

    // +1 to account for the NUL byte
    char *dup = (char *) malloc(len + 1);
    if (!dup) {
        return NULL;
    }

    // Copy each char from `s` to `dup`
    int i;
    for (i = 0; s[i] != '\0'; i++) {
        dup[i] = s[i];
    }

    // Ensure `dup` is NUL terminated
    dup[i] = '\0';

    return dup;
}

int main(int argc, char *argv[])
{
    int i;
    for (i = 0; i < argc; i++) {
        char *dup = strdup209(argv[i]);
        printf("strdup(argv[%d]) = \"%s\"\n", i, dup);
        free(dup);
    }
    
    return 0;
}
