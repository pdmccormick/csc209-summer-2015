#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "waithelper.h"

static int cat_fd(int in_fd, int out_fd, char *prefix);

static int parent_process(char *filename, pid_t child, int pipefds[2]);
static int child_process(int pipefds[2]);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *filename = argv[1];

    /* Setup pipe (parent => child) */
    int pipefds[2];
    if (pipe(pipefds) < 0) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    /* Fork off child */
    pid_t child = fork();

    if (child < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    /** TODO Exercise: Remove some of the close() calls and notice how the EOF behaviour breaks */

    if (child == 0) {
        return child_process(pipefds);
    }
    else {
        return parent_process(filename, child, pipefds);
    }

    // Should never get here
    return EXIT_FAILURE;
}

static int parent_process(char *filename, pid_t child, int pipefds[2])
{
    fprintf(stderr, "parent: pid %ld\n", (long) getpid());
    fprintf(stderr, "parent: pipe read-fd %d, write-fd %d\n", pipefds[0], pipefds[1]);

    int fd = open(filename, O_RDONLY);

    if (fd < 0) {
        fprintf(stderr, "Unable to open %s for reading", filename);
        perror("open");
        return EXIT_FAILURE;
    }

    fprintf(stderr, "parent: file fd=%d\n", fd);

    // Parent is not reading from pipe (only writing)
    close(pipefds[0]);

    const int write_pipe = pipefds[1];

    // Write contents of file into pipe
    cat_fd(fd, write_pipe, "parent");

    // No more writing to this pipe (will signal EOF to readers)
    close(write_pipe);

    close(fd);

    // Wait for child to finish
    wait_for_child(child);

    return EXIT_SUCCESS;
}

static int child_process(int pipefds[2])
{
    // Child is not writing into pipe (only reading)
    close(pipefds[1]);

    const int read_pipe = pipefds[0];

    fprintf(stderr, "child: pid %ld, parent pid %ld\n", (long) getpid(), (long) getppid());

    // Read contents of pipe and write to stdout
    cat_fd(read_pipe, STDOUT_FILENO, "child");

    // No more reading from this pipe
    close(read_pipe);

    return EXIT_SUCCESS;
}

static int cat_fd(int in_fd, int out_fd, char *prefix)
{
    // 128 KB buffer
    static char buf[128 * 1024];
    const size_t buf_size = sizeof (buf);

    while (1) {
        ssize_t read_len = read(in_fd, buf, buf_size);
        fprintf(stderr, "%s: fd=%d: read %zd bytes\n", prefix, in_fd, read_len);

        if (read_len < 0) {
            perror("read");
            return -1;
        }
        else if (read_len == 0) {
            break;
        }

        ssize_t write_len = write(out_fd, buf, read_len);
        fprintf(stderr, "%s: fd=%d: wrote %zd bytes\n", prefix, out_fd, write_len);

        if (write_len < 0) {
            perror("write");
            return -1;
        }
        else if (write_len != read_len) {
            fprintf(stderr, "ERROR: read %zd bytes but only wrote %zd\n", read_len, write_len);
            return -1;
        }
    }

    return 0;
}
