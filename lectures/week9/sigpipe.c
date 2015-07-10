#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "waithelper.h"

int main(int argc, char *argv[])
{
    int pipefds[2];

    if (pipe(pipefds) < 0) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    // Close the read end of this pipe
    close(pipefds[0]);

    pid_t child = fork();
    if (child < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (child == 0) {
        // Child
        printf("child: attempting to write to a pipe with closed read end...\n");
        
        // Attempt to write to the pipe
        char c = 'X';
        write(pipefds[1], &c, 1);

        printf("child: success?!\n");
    }
    else {
        // Parent

        // Close the write end too
        close(pipefds[0]);

        // Reap child
        wait_for_child(child);
    }

    return EXIT_SUCCESS;
}
