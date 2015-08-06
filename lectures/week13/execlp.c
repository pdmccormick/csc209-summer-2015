#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("Running /bin/ls...\n");

    execlp("/bin/ls",
            "ls",
            "-l",
            (char *) NULL /* <== NULL terminated */,
            "also ignored");

    perror("execlp");

    return EXIT_FAILURE;
}
