#ifndef __WAITHELPER_H
#define __WAITHELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include "signal2str.h"

static void wait_for_child(pid_t child)
{
    int status;
    do {
        pid_t w;

        w = waitpid(child, &status, WUNTRACED | WCONTINUED);

        if (w < 0) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            int exitcode = WEXITSTATUS(status);
            printf("child pid %ld exited with exit code %d\n", (long) w, exitcode);
        }
        else if (WIFSIGNALED(status)) {
            int termsig = WTERMSIG(status);
            printf("child pid %ld was terminated by signal SIG%s (#%d)\n", (long) w, signal2str(termsig), termsig);
        }
        else if (WIFSTOPPED(status)) {
            int stopsig = WSTOPSIG(status);
            printf("child pid %ld was stopped by signal SIG%s (#%d)\n", (long) w, signal2str(stopsig), stopsig);
        }
        else if (WIFCONTINUED(status)) {
            printf("child pid %ld continued\n", (long) w);
        }
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
}

#endif /* __WAITHELPER_H */
