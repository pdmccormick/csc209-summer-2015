#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Create a typedef for easier casting
typedef int (*qsort_comparison)(const void *, const void *);

// `qsort` will pass the comparison function a pointer to something, and in our
// case that something is itself a `char *`, hence we will be receiving `char
// **` as arguments
int my_strcmp(const char **s1, const char **s2)
{
    int rc;

    rc = strcmp(*s1, *s2);

    printf("strcmp(\"%s\", \"%s\") = %d\n", *s1, *s2, rc);

    return rc;
}

int main(int argc, char *argv[])
{
    // Perform a sort on `argv` (offset by 1 to avoid `argv[0]`)
    qsort((void *) (argv + 1), argc - 1, sizeof (*argv), (qsort_comparison) my_strcmp);
    printf("\n");

    int i;
    for (i = 1; i < argc; i++) {
        printf("[%d] = \"%s\"\n", i, argv[i]);
    }

    return 0;
}
