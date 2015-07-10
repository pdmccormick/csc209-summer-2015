#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
 * Implement a simple one argument version of `cat(1)` using raw file
 * descriptors for reading & writing
 */
int main(int argc, char *argv[])
{
    int rc;
    int fd;

    if (argc != 2) {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        return -1;
    }

    char *filename = argv[1];

    // Open the file
    fd = open(filename, O_RDONLY);

    if (fd < 0) {
        fprintf(stderr, "Unable to open %s for reading\n", filename);
        perror("open");
        return -1;
    }

    // NB: File descriptor `fd` is now open and ready for reading!

    char buf[128];
    ssize_t read_len, write_len;

    while (1) {
        // Read in a chunk of the buffer
        read_len = read(fd, buf, sizeof (buf));

        if (read_len < 0) {
            // A negative return value from read(2) indicates some kind of internal error
            perror("read");
            return -1;
        }
        else if (read_len == 0) {
            // A return value of 0 from read(2) indicates EOF
            break;
        }

        write_len = write(STDOUT_FILENO, buf, read_len);

        if (write_len < 0) {
            perror("write");
            return -1;
        }
        else if (write_len != read_len) {
            /* NB: This should not be an error, because write(2) does not
             * guarantee that it will write all the bytes you ask it to...
             */
            fprintf(stderr, "ERROR: read %zd bytes but only wrote %zd\n", read_len, write_len);
            return -1;
        }
    }

    // Close the file descriptor
    rc = close(fd);
    if (rc < 0) {
        perror("close");
        return -1;
    }

    return 0;
}
