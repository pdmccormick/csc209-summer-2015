#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#include "signal2str.h"

#define NUM_SIGNALS     32

static void my_signal_handler(int sig);

/**
 * Setup a signal handler for all signal numbers.
 *
 * NB: You will have to `kill -9` in order to end this program!!!
 */
int main(int argc, char *argv[])
{
    struct sigaction act;

    act.sa_handler = my_signal_handler;
    act.sa_flags = 0;

    int i;
    for (i = 1; i < NUM_SIGNALS; i++) {
        int rc = sigaction(i, &act, NULL);
        if (rc) {
            if (errno == EINVAL) {
                fprintf(stderr, "WARNING: Unable to setup a handler for SIG%s (#%d)\n", signal2str(i), i);
                continue;
            }

            fprintf(stderr, "SIG%s (#%d): ", signal2str(i), i);
            perror("signal");
            return -1;
        }
    }

    pid_t my_pid = getpid();

    printf("%ld\n", (long) my_pid);

    while (1) {
        fprintf(stderr, "Pausing pid %ld...\n", (long) my_pid);
        pause();
    }

    return 0;
}

void my_signal_handler(int sig)
{
    printf("Handling SIG%s (#%d)\n", signal2str(sig), sig);

    if (sig == SIGINT) {
        printf("Exiting...\n");
        exit(EXIT_SUCCESS);
    }
}
