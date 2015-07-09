#include <stdio.h>
#include <unistd.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    printf("stdin  FD %d\n", STDIN_FILENO);
    printf("stdout FD %d\n", STDOUT_FILENO);
    printf("stderr FD %d\n", STDERR_FILENO);

    assert(STDIN_FILENO == fileno(stdin));
    assert(STDOUT_FILENO == fileno(stdout));
    assert(STDERR_FILENO == fileno(stderr));

    return 0;
}
