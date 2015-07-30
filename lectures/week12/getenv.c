#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s name\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *name = argv[1];
    
    /* Get the named environment variable */
    char *val = getenv(name);

    if (val == NULL) {
        printf("%s does not exist\n", name);
    }
    else {
        printf("%s=%s\n", name, val);
    }

    return EXIT_SUCCESS;
}
