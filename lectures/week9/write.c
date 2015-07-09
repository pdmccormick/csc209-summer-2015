#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

const size_t buf_size = 64 * 1024; // 64 KB

int main(int argc, char *argv[])
{
    // Allocate space for our buffer
    void *buf = malloc(buf_size);

    if (buf == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    // Zero it out
    memset(buf, 0, buf_size);

    char *filename = "zero.bin";

    // Open the file
    int fd;

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror(filename);
        return EXIT_FAILURE;
    }

    printf("opened %s\n", filename);

    size_t total_written = 0;
    size_t attempted_written = 0;

    // Attempt to write 1 MB of zero's (16 * 64 KB)
    int i;
    for (i = 0; i < 16; i++) {
        ssize_t written = write(fd, buf, buf_size);

        total_written += written;
        attempted_written += buf_size;

        // You will generally observe `written == buf_size`, but that is not guaranteed...

        printf("write of %zu bytes returned %zd bytes\n", buf_size, written);
    }

    // For files, this MAY typically be 0
    size_t difference = attempted_written - total_written;

    printf("attempted to write %zu bytes, actually wrote %zu bytes (difference %zu)\n",
        attempted_written,
        total_written,
        difference);

    close(fd);

    return EXIT_SUCCESS;
}
