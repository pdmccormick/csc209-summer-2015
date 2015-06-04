#include <stdio.h>
#include <string.h>
#include <libgen.h>

/*
 * Here we investigate a quirk of the return values of `dirname(3)`.
 */
int main(int argc, char *argv[])
{
    char *path = "/u/csc209h/summer/pub/bin";

    printf("path: %s\n", path);

    char *dir1 = dirname(path);
    printf("dir1: %s\n", dir1);

    char *dir2 = dirname(dir1);
    printf("dir2: %s\n", dir2);

    char *dir3 = dirname(dir2);
    printf("dir3: %s\n", dir3);

    char *dir4 = dirname(dir3);
    printf("dir4: %s\n", dir4);

    char *dir5 = dirname(dir4);
    printf("dir5: %s\n", dir5);
    printf("\n");

    /*
    if (1) {
        // Show all the dir's again
        printf("dir1: %s\n", dir1);
        printf("dir2: %s\n", dir2);
        printf("dir3: %s\n", dir3);
        printf("dir4: %s\n", dir4);
        printf("dir5: %s\n", dir5);
        printf("\n");
    }
    */









    /*
    if (1) {
        // What's happening?
        printf("   dir1 %p\n", dir1);
        printf("   dir2 %p\n", dir2);
        printf("   dir3 %p\n", dir3);
        printf("   dir4 %p\n", dir4);
        printf("   dir5 %p\n", dir5);
        printf("\n");
    }
    */

    return 0;
}
