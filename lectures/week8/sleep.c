#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int duration = 1;

    if (argc > 1) {
        duration = atoi(argv[1]);
    }

    pid_t pid = getpid();

    while (1) {
        printf("pid %ld sleeping for %d\n", (long) pid, duration);
        sleep(duration);
    }

    return 0;
}
