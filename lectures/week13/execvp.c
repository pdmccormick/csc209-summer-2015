#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char **ls_argv = malloc(4 * sizeof (char *));

    ls_argv[0] = "ls";
    ls_argv[1] = "-l";
    ls_argv[2] = NULL;
    ls_argv[3] = "ignored";

    printf("Running /bin/ls...\n");

    execvp("/bin/ls", ls_argv);

    perror("execvp");

    return EXIT_FAILURE;
}
