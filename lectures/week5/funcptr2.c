#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    void *(*malloc_fptr)(size_t) = malloc;
    printf("malloc      = %p\n", malloc);
    printf("malloc_fptr = %p\n", malloc_fptr);
    printf("\n");

    FILE *(*fopen_fptr)(const char *fn, const char *m) = fopen;
    printf("fopen       = %p\n", fopen);
    printf("fopen_fptr  = %p\n", fopen_fptr);
    printf("\n");

    return 0;
}
