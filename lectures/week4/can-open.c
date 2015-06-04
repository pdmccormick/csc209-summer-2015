#include <stdio.h>

/**
 * Check if a filename can be open
 */
int main(int argc, char *argv[])
{
    // Show a usage message if program not passed a filename argument
    if (argc != 2) {
        printf("usage: %s filename\n", argv[0]);
        return -1;
    }

    // Open the first argument filename for reading
    FILE *fp = fopen(argv[1], "r");

    // Check for a NULL pointer
    if (fp == NULL) {
        printf("ERROR: Unable to open %s\n", argv[1]);
        return -2;
    }

    // Don't forget to close the file once you're done with it
    fclose(fp);

    return 0;
}
