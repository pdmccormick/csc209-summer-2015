#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int duration = 1;
    const int num = 1024 * 1024 * 1024;

    if (argc > 1) {
        duration = atoi(argv[1]);
    }

    pid_t pid = getpid();

    while (1) {
        printf("pid %ld sleeping for %d\n", (long) pid, duration);
        sleep(duration);

        // Waste CPU time
        printf("computing\n");
        int i;
        int k = 1;
        for (i = 1; i < num; i++) {
            k = k + i;
        }
    }

    return 0;
}
