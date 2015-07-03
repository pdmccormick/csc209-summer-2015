#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

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
        // Child (with original parent)
        printf("child: pid %ld, parent pid %ld\n", (long) getpid(), (long) getppid());

        printf("child: hit enter to let the child exit\n");
        fgetc(stdin);

        printf("child: parent pid is still %ld\n", (long) getppid());

        printf("child: exiting with code %d\n\n", child_exitcode);
        exit(child_exitcode);
    }
    else {
        // Parent
        printf("parent: pid %ld\n", (long) getpid());

        printf("parent: waiting for child status\n");
        int status;
        pid_t w = wait(&status);

        printf("parent: child pid %ld exited with status 0x%x\n", (long) w, status);

        // These all-caps functions/macros (see manpage) will extract info from `status`

        // Wait - If Exited
        if (WIFEXITED(status)) {
            // Wait - Exit Status
            int exitcode = WEXITSTATUS(status);
            printf("parent: child exited normally with exit code %d\n", exitcode);
        }

        // Wait - If Signaled
        if (WIFSIGNALED(status)) {
            // Wait - Terminating Signal
            int termsig = WTERMSIG(status);
            printf("parent: child process was terminated by signal '%s' (%d)\n", sys_signame[termsig], termsig);
        }

        printf("parent: exiting\n");
    }

    return 0;
}
