#include <stdio.h>
#include <unistd.h>

/**
 * Uses the `execvp` system call to replace the currently running process.
 */
int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s bin_name [args...]\n", argv[0]);
        return -1;
    }

    char *bin_name = argv[1];

    printf("pid %ld, parent pid %ld\n\n", (long) getpid(), (long) getppid());

    /* Call `execvp` using all of the arguments we were passed (excluding the
     * name of our own executable program) */
    if (execvp(bin_name, argv + 1)) {
        fprintf(stderr, "execvp(\"%s\", ...): ", bin_name);
        perror("");
        return -1;
    }

    printf("We should never execute this...\n");

    return 0;
}
