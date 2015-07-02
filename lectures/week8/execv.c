#include <stdio.h>
#include <unistd.h>

/**
 * Uses the `execv` system call to replace the currently running process.
 */
int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s bin_path [args...]\n", argv[0]);
        return -1;
    }

    char *bin_path = argv[1];

    printf("pid %ld, parent pid %ld\n\n", (long) getpid(), (long) getppid());

    /* Call `execv` using all of the arguments we were passed (excluding the
     * name of our own executable program) */
    if (execv(bin_path, argv + 1)) {
        fprintf(stderr, "execv(\"%s\", ...): ", bin_path);
        perror("");
        return -1;
    }

    printf("We should never execute this...\n");

    return 0;
}
