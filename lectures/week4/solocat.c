#include <stdio.h>
#include <assert.h>

/**
 * Implement a simple one argument, file only version of `cat(1)`
 */
int main(int argc, char *argv[])
{
    /* Show a usage message if program not passed a filename argument */
    if (argc != 2) {
        printf("usage: %s filename\n", argv[0]);
        return -1;
    }

    /* Open the first argument filename for reading */
    FILE *fp = fopen(argv[1], "r");

    /* Check for a NULL pointer (which indicates error opening) */
    if (fp == NULL) {
        printf("ERROR: Unable to open %s\n", argv[1]);
        perror("fopen");
        return -2;
    }

    /* Get one character at a time, until End of File (EOF) */
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        unsigned char c = (unsigned char) ch;
        printf("%c", c);
    }

    assert(feof(fp));

    /* Don't forget to close the file once you're done with it */
    fclose(fp);

    return 0;
}
