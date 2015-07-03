#include <stdio.h>
#include <string.h>

/**
 * Uses `strstr` to find one string (the "needle") in another (the "haystack")
 *
 * Try:
 *
 *      $ ./strstr "UofT CSC209" CSC
 *
 *  Or,
 *      $ ./strstr "UofT CSC209" 207
 */
int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("usage: %s haystack needle\n", argv[0]);
        return -1;
    }

    char *haystack = argv[1];
    char *needle = argv[2];

    char *s = strstr(haystack, needle);
    if (!s) {
        printf("\"%s\" not found in \"%s\"\n", needle, haystack);
        return -1;
    }

    printf("Found \"%s\" in \"%s\" at offset %tu: %s\n",
            needle, haystack,
            s - haystack,
            s);

    return 0;
}
