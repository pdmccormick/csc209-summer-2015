#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void) {
    int fd;
    int count;

    fd = open("output.txt", O_WRONLY | O_CREAT);

    if (fd < 0) {
        printf("Cannot open output.txt for writing\n");
        perror("open");
        return -1;
    }

    count = write(fd, "Hello world!", sizeof ("Hello world!") - 1);

    /* TODO: Unless `count == strlen("Hello World!")`, not all of the bytes we were
     * expecting to be written necessarily have been. */
    if (count < 0) {
        perror("write");
        return -1;
    }

    if (close(fd) < 0) {
        perror("close");
        return -1;
    }

    return 0;
}

