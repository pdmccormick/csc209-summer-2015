#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t child = fork();

    if (child < 0) {
        perror("fork");
        return -1;
    }

    if (child == 0) {
        // Child (with original parent)
        printf("child: pid %ld, parent pid %ld\n", (long) getpid(), (long) getppid());

        // Wait 2 seconds, giving the parent the chance to terminate abruptly
        printf("child: sleeping 2 seconds\n");
        sleep(2);

        // Now that our original parent should be gone, check again who are parent is
        printf("child: parent pid is now %ld\n", (long) getppid());

        printf("child: exiting\n");
    }
    else {
        // Parent
        printf("parent: pid %ld\n", (long) getpid());

        // Sleep for 1 second (giving the child a chance to run and print its initial parent PID)
        printf("parent: sleeping 1 second\n");
        sleep(1);

        // Exit without accepting the child processes' status code
        printf("parent: exiting\n");
    }

    return 0;
}
