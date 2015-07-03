#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Perform a `strncat` into a too small buffer.
 *
 * Try:
 *      $ ./strcpy3 15 SummerCSC209
 *
 *  Notice that `strncat` is NOT copying the NUL from `src` if `n < strlen(src)`:
 *
 *      $ ./strcpy3 10 SummerCSC209
 *
 *  The extra '#' padding characters are ones we specifically chose to show
 *  this behaviour. If we had not done that, there would have been no NUL and
 *  `printf` or any other function expecting a string might have continued
 *  reading memory way past the end of the space allocated for `s`.
 */
int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("usage: %s len src\n", argv[0]);
        return -1;
    }

    // Collect arguments
    size_t len = atoi(argv[1]);
    char *src = argv[2];

    // Allocate enough space for destination, with some padding
    size_t pad = 16;
    char *dest = (char *) malloc(len + pad);

    if (!dest) {
        perror("malloc");
        return -1;
    }

    // Provide a safety net in the event that `strncpy` does not copy the NUL byte
    memset(dest, '#', len + pad);
    dest[len + pad - 1] = '\0';

    // Destination is initially empty
    dest[0] = '\0';

    // Do a limited copy
    strncpy(dest, src, len);

    /* Uncomment the following line to be safe even when `n < strlen(src)`. You
     * can only do this is you allocated at least `len + 1` bytes for `dest`.
     * */
    //dest[len] = '\0';

    printf("src : %s\n", src);
    printf("dest: %s\n", dest);

    return 0;
}
