#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("usage: %s array-size\n", argv[0]);
        return -1;
    }

    int size = atoi(argv[1]);
    printf("size = %d\n", size);

    int *array;

    // TODO: Allocate dynamic memory to hold array

    return 0;
}
