#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "signal2str.h"
#include "waithelper.h"

static int cat_fd(int in_fd, int out_fd);

int main(int argc, char *argv[])
{
    int rc;
    int fd;

    if (argc != 2) {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *filename = argv[1];

    fd = open(filename, O_RDONLY);

    if (fd < 0) {
        fprintf(stderr, "Unable to open %s for reading", filename);
        perror("open");
        return EXIT_FAILURE;
    }

    // Fork a child process
    pid_t child;
    child = fork();
    if (child < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (child == 0) {
        // Child
        fprintf(stderr, "child: pid %ld, parent pid %ld\n", (long) getpid(), (long) getppid());

        // Child cats from fd to stdout
        fprintf(stderr, "child: cat\n");
        cat_fd(fd, STDOUT_FILENO);

        exit(EXIT_SUCCESS);
    }
    else {
        // Parent
        fprintf(stderr, "parent : pid %ld\n", (long) getpid());

        // Wait for child to finish
        wait_for_child(child);

        // Now parent cats from fd to stdout
        fprintf(stderr, "parent: cat\n");

        /* Uncomment the following to prove that the file is still open for the
         * parent, but simply that it was at EOF */
        //lseek(fd, 0, SEEK_SET);

        cat_fd(fd, STDOUT_FILENO);

        fprintf(stderr, "parent: done\n");
    }

    rc = close(fd);
    if (rc < 0) {
        perror("close");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

static int cat_fd(int in_fd, int out_fd)
{
    char buf[128];
    ssize_t read_len, write_len;

    while (1) {
        read_len = read(in_fd, buf, sizeof (buf));

        if (read_len < 0) {
            perror("read");
            return -1;
        }
        else if (read_len == 0) {
            break;
        }

        write_len = write(out_fd, buf, read_len);

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

