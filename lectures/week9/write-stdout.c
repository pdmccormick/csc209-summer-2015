#include <stdio.h>
#include <unistd.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    // Write to stdout
    char msg[] = "Hello World via write(2)!";

    // -1 because we do NOT want to write the NUL terminating byte
    size_t msg_len = sizeof (msg) - 1;

    ssize_t written = write(STDOUT_FILENO, msg, msg_len);

    // Hopefully all we asked for was actually written (this is NOT guaranteed)
    assert (written == msg_len);

    return 0;
}
