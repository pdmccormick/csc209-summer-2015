#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    printf("%s: pid %ld, parent pid %ld\n",
            argv[0],
            (long) getpid(),
            (long) getppid());

    pause();

    return 0;
}
