#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>

int main(int argc, char *argv[])
{
    while (1) {
        int activity = 0;

        // 1) Setup the read FD set (with only a single descriptor)
        fd_set readfds;

        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        int max_fd = STDIN_FILENO;

        // 2) Setup a two second timeout duration
        struct timeval timeout;
        timeout.tv_sec = 2;
        timeout.tv_usec = 0;

        // 3) Issue select call for read set with timeout
        int rc = select(max_fd + 1, &readfds, NULL, NULL, &timeout);
        if (rc < 0) {
            switch (errno) {
            default:
                perror("select");
                exit(EXIT_FAILURE);
            }
        }
        else if (rc > 0) {
            // There was some activity registered
            activity = 1;
        }

        // 4) Check for the presence of STDIN in the read set
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            char buf[128 + 1];

            // Perform I/O on ready descriptor
            ssize_t bytes_read = read(STDIN_FILENO, buf, sizeof (buf) - 1);

            if (bytes_read < 0) {
                perror("read");
                exit(EXIT_FAILURE);
            }
            else if (bytes_read == 0) {
                // EOF
                fprintf(stderr, "Goodbye!\n");
                exit(EXIT_SUCCESS);
            }
            else {
                buf[bytes_read] = '\0';
                printf("stdin: %s\n", buf);
            }
        }

        // If no activity, we must have timed out...
        if (!activity) {
            static int num_timeouts = 1;
            fprintf(stderr, "Timeout %d...\n", num_timeouts++);
        }
    }

    return 0;
}
