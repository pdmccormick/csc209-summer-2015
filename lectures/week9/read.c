#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

const size_t buf_size = 1024 * 1024; // 1 MB
char *default_filename = "csc209-week9-20150709.pdf";

int main(int argc, char *argv[])
{
    // Allocate space for our large buffer
    void *buf = malloc(buf_size);

    if (buf == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    char *filename = default_filename;
    if (argc > 1) {
        filename = argv[1];
    }

    // Open the file
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror(filename);
        return EXIT_FAILURE;
    }

    printf("opened %s\n", filename);

    // Attempt to read it in very large strides
    while (1) {
        ssize_t bytes_read = read(fd, buf, buf_size);

        printf("read of %zu bytes returned %zd bytes\n", buf_size, bytes_read);

        // Returns 0 when we are done
        if (bytes_read == 0) {
            break;
        }
    }
    
    // Close descriptor and cleanup
    close(fd);

    free(buf);

    return EXIT_SUCCESS;
}
