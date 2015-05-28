#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;

    for (i = 0; i < argc; i++) {
        printf("[%d] = '%s'\n", i, argv[i]);
    }
    printf("\n");

    printf("argv      = %p\n", argv);

    for (i = 0; i < argc; i++) {
        unsigned long addr_argv_i = (unsigned long) &argv[i];
        printf("&argv[%d]  = 0x%lx\n", i, addr_argv_i);

        //printf("[%d] = '%s'\n", i, argv[i]);
    }
    printf("\n");

    unsigned long last = 0;
    for (i = 0; i < argc; i++) {
        unsigned long cur = (unsigned long) argv[i];
        unsigned long diff = cur - last;

        if (last == 0) {
            printf("argv[%d]   = 0x%lx\n", i, cur);
        }
        else {
            printf("argv[%d]   = 0x%lx  (diff %2ld)\n", i, cur, diff);
        }

        last = cur;
    }

    return 0;
}
