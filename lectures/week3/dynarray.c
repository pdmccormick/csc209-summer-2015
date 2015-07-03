#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("usage: %s array-size\n", argv[0]);
        return -1;
    }

    /* `atol` takes a C-style string (a NUL-terminated `char *` aka char
     * array), interprets the ASCII characters as a decimal integer and returns
     * the equivilent `long` (64 bit) integer.
     *
     * `atoi` does the same thing but returns an `int` (32 bit) integer.
     */
    unsigned long size = atol(argv[1]);
    printf("size = %lu\n", size);

    long *array;
  
    /* We want to allocate an array with `size` elements, each of which will
     * take require `sizeof (long)` bytes of memory for storage. So the overall
     * requested allocation size needs to be the product of those two values.
     * */ 
    array = (long *) malloc(size * sizeof (long));

    if (array == NULL) {
        perror("malloc failed\n");
        return 0;
    }

    /* Once the memory has been allocated, we can store to and load from any
     * part of it. */
    int i;
    for (i = 0; i < size; i++) {
        array[i] = i;
    }

    /* Once you are sure that you are done using it, free (release/return) your
     * memory or else it will be lost for any further use by this process.
     *
     * Remember, there is no language runtime that will identify "garbage"
     * (unreferenced memory) and reuse it!
     */
    free(array);

    return 0;
}
