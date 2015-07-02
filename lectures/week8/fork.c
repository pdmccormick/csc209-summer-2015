#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("before fork: pid %ld, parent pid %ld\n\n", (long) getpid(), (long) getppid());

    // Fork this process in order to create a child
    pid_t child = fork();

    // Fork returns a negative value (-1) if the system call failed
    if (child < 0) {
        perror("fork");
        return -1;
    }

    if (child == 0) {
        // Fork return 0, meaning we are the child process
        printf("child: pid %ld, parent pid %ld\n", (long) getpid(), (long) getppid());
    }
    else {
        // Fork returned a positive value, meaning we are the original parent process
        printf("parent: pid %ld\n", (long) getpid());
    }

    pause();

    return 0;
}
