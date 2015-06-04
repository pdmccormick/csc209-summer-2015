#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * Implement a simple one argument, file only version of `cat(1)`
 */
int main(int argc, char *argv[])
{
    const int max_chunk_size = 40;
    unsigned char buf[max_chunk_size + 1];

    // Show a usage message if program not passed enough arguments
    if (argc != 4) {
        printf("usage: %s chunk-size padding filename\n", argv[0]);
        return -1;
    }

    int chunk_size = atoi(argv[1]);
    char *pad = argv[2];
    char *filename = argv[3];

    if (chunk_size > max_chunk_size) {
        printf("ERROR: Maximum supported chunk size is 40\n");
        return -2;
    }

    // Open the first argument filename for reading
    FILE *fp = fopen(filename, "r");

    // Check for a NULL pointer (which indicates error opening)
    if (fp == NULL) {
        printf("ERROR: Unable to open %s\n", filename);
        perror("fopen");
        return -2;
    }

    // Get a chunk at a time
    while (!feof(fp)) {
        size_t bytes_read = fread(buf, 1, chunk_size, fp);

        if (bytes_read == 0) {
            continue;
        }

        assert(bytes_read <= chunk_size);

        buf[bytes_read] = '\0';
        printf("%s%s", buf, pad);
    }

    // Don't forget to close the file once you're done with it
    fclose(fp);

    return 0;
}
