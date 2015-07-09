#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int rc;
    ssize_t len;

    // 0 is read end, 1 is write end
    int pipefds[2];

    // Setup a pair of pipe file descriptors (FD's)
    rc = pipe(pipefds);
    if (rc) {
        perror("pipe");
        return -1;
    }

    printf("pipe(2) returned read-fd %d, write-fd %d\n\n", pipefds[0], pipefds[1]);

    // Write some data into the write end of the pipe
    char msg[] = "Pipes!";

    printf("writing: %s (%zu bytes to fd=%d)\n", msg, sizeof (msg), pipefds[1]);
    len = write(pipefds[1], msg, sizeof (msg));

    // write(2) returns < 0 on error
    if (len < 0) {
        perror("write");
        return -1;
    }

    printf("wrote %zd bytes\n\n", len);

    // Read that same back out of the read-end of the pipe
    char recv_msg[128] = {};

    len = read(pipefds[0], recv_msg, sizeof (recv_msg));

    // read(2) returns < 0 on error
    if (len < 0) {
        perror("read");
        return -1;
    }

    printf("read %zd bytes from fd=%d\n", len, pipefds[0]);
    printf("received: %s\n", recv_msg);

    return 0;
}
