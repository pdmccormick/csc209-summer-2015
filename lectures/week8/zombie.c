#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#include "signal2str.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s exitcode\n", argv[0]);
        return -1;
    }

    int child_exitcode = atoi(argv[1]);

    pid_t child = fork();

    if (child < 0) {
        perror("fork");
        return -1;
    }

    if (child == 0) {
        // Child
        printf("child: pid %ld, parent pid %ld\n", (long) getpid(), (long) getppid());
        printf("child: exiting with code %d\n\n", child_exitcode);

        // Exit with specific code
        exit(child_exitcode);
    }
    else {
        // Parent
        printf("parent: pid %ld\n", (long) getpid());

        // First delay ...
        printf("parent: press enter and then parent will wait for child\n");
        fgetc(stdin);

        // .. and then wait()
        printf("parent: waiting for child status\n");
        int status;
        pid_t w = wait(&status);

        printf("parent: child pid %ld exited with status 0x%x\n", (long) w, status);

        if (WIFEXITED(status)) {
            int exitcode = WEXITSTATUS(status);
            printf("parent: child exited normally with exit code %d\n", exitcode);
        }

        if (WIFSIGNALED(status)) {
            int termsig = WTERMSIG(status);
            printf("parent: child process was terminated by signal SIG%s (#%d)\n", signal2str(termsig), termsig);
        }

        printf("parent: exiting\n");
    }

    return 0;
}
