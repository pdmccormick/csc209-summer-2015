#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s num_children [exitcode]\n", argv[0]);
        return -1;
    }

    int num_children = atoi(argv[1]);
    int do_child_exit = (argc >= 3);
    int child_exitcode_base = 0;

    if (do_child_exit) {
        child_exitcode_base = atoi(argv[2]);
    }

    // Fork `num_children` new processes
    int i;
    for (i = 0; i < num_children; i++) {
        pid_t child = fork();

        if (child == -1) {
            perror("fork");
            return -1;
        }

        if (child != 0) {
            // This is the parent, so just carry on
            continue;
        }

        // child==0 so we are the child

        printf("child #%d: pid %ld, parent pid %ld\n", i, (long) getpid(), (long) getppid());

        // Wait a moment before proceeding
        sleep(1);

        if (do_child_exit) {
            int exitcode = child_exitcode_base + i;
            printf("child #%d: exiting with code %d\n", i, exitcode);
            exit(exitcode);
        }
        else {
            /* Wait for signals (can only terminate) */
            pause();

            printf("child #%d: should never return here...\n", i);
            exit(-1);
        }
    }

    printf("\n");

    // We are now the parent of `num_children` processes
    printf("parent: pid %ld\n", (long) getpid());

    int num_exited = 0;
    int status;

    while (num_exited < num_children) {
        pid_t w;

        // Wait for any child
        w = waitpid(-1, &status, WUNTRACED | WCONTINUED);

        if (w < 0) {
            perror("waitpid");
            return -1;
        }

        if (WIFEXITED(status)) {
            int exitcode = WEXITSTATUS(status);
            printf("parent: child pid %ld exited normally with exit code %d\n", (long) w, exitcode);
            num_exited++;
        }
        else if (WIFSIGNALED(status)) {
            int termsig = WTERMSIG(status);
            printf("parent: child pid %ld was terminated by signal '%s' (%d)\n", (long) w, sys_signame[termsig], termsig);
            num_exited++;
        }
        else if (WIFSTOPPED(status)) {
            int stopsig = WSTOPSIG(status);
            printf("parent: child pid %ld was stopped by signal '%s' (%d)\n", (long) w, sys_signame[stopsig], stopsig);
        }
        else if (WIFCONTINUED(status)) {
            printf("parent: child pid %ld continued\n", (long) w);
        }
    }

    printf("parent: all children collected\n");

    return 0;
}
