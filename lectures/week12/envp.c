#include <stdio.h>
#include <stdlib.h>

/**
 * This is the true signature for the main() function on Linux
 */
int main(int argc, char *argv[], char *envp[])
{
    char **cur = envp;
    while (*cur != NULL) {
        printf("%s\n", *cur);
        cur++;
    }

    return 0;
}
