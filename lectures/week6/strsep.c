#include <stdio.h>
#include <string.h>

/**
 * Use `strsep` to tokenize a string.
 *
 * Try:
 *
 *      $ ./strsep ' ' "Hello CSC209 World!"
 *
 *  Or,
 *
 *      $ ./strsep '!@$%*' 'Can!anyone@hear$me%in*here?'
 */
int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("usage: %s delim \"str\"\n", argv[0]);
        return -1;
    }

    char *delim = argv[1];
    char *str = strdup(argv[2]);

    if (!str) {
        perror("strdup");
    }

    // NB: We create a duplicate of `argv[2]` because `strsep` will modify it

    char *cur = str;
    while (cur) {
        char *next = cur;
        strsep(&next, delim);

        printf("token: %s\n", cur);

        cur = next;
    }

    free(str);

    return 0;
}
