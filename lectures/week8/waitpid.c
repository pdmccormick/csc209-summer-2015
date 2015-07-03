#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t child;

    child = fork();
    if (child == -1) {
        perror("fork");
        return -1;
    }

    if (child == 0) {
        /* Code executed by child */
        printf("child: pid %ld, parent pid %ld\n", (long) getpid(), (long) getppid());

        if (argc == 1) {
            /* Wait for signals */
            pause();
        }

        exit(atoi(argv[1]));
    }
    else {
        /* Code executed by parent */
        printf("parent : pid %ld\n", (long) getpid());

        int status;
        do {
            pid_t w;

            w = waitpid(child, &status, WUNTRACED | WCONTINUED);

            if (w < 0) {
                perror("waitpid");
                return -1;
            }

            if (WIFEXITED(status)) {
                int exitcode = WEXITSTATUS(status);
                printf("parent: child pid %ld exited normally with exit code %d\n", (long) w, exitcode);
            }
            else if (WIFSIGNALED(status)) {
                int termsig = WTERMSIG(status);
                printf("parent: child pid %ld was terminated by signal '%s' (%d)\n", (long) w, sys_signame[termsig], termsig);
            }
            else if (WIFSTOPPED(status)) {
                int stopsig = WSTOPSIG(status);
                printf("parent: child pid %ld was stopped by signal '%s' (%d)\n", (long) w, sys_signame[stopsig], stopsig);
            }
            else if (WIFCONTINUED(status)) {
                printf("parent: child pid %ld continued\n", (long) w);
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 0;
}
