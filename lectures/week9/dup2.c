#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int pipefds[2];

    // Child => Parent
    if (pipe(pipefds) < 0) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    printf("pipe read-fd %d, write-fd %d\n", pipefds[0], pipefds[1]);

    pid_t child = fork();
    if (child < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (child == 0) {
        // Child

        // Child => Parent
        close(pipefds[0]);

        // Make the stdout FD actually be the write end of the pipe
        if (dup2(pipefds[1], STDOUT_FILENO) < 0) {
            perror("dup2");
            return EXIT_FAILURE;
        }

        // Write something to the standard output
        fprintf(stdout, "Child wrote this to stdout!");
        fflush(stdout);
    }
    else {
        // Parent

        // Child => Parent
        close(pipefds[1]);

        char buf[64 + 1];
        while (1) {
            ssize_t read_bytes = read(pipefds[0], buf, sizeof (buf) - 1);
            if (read_bytes < 0) {
                perror("read");
                return EXIT_FAILURE;
            }
            else if (read_bytes == 0) {
                break;
            }

            buf[read_bytes] = '\0';
            fprintf(stderr, "parent: fd %d: read %zd bytes: \"%s\"\n", pipefds[0], read_bytes, buf);
        }

        // Wait for child to terminate
        int status;
        wait(&status);
    }

    return EXIT_SUCCESS;
}
