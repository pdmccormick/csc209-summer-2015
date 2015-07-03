#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Try this out as:
 *      $ gcc -Wall -g exitstatus.c -o exitstatus
 *      $ ./exitstatus 10
 *      $ echo $?
 *      10
 *
 *      $ ./exitstatus -1
 *      $ echo $?
 *      255
 *
 * Remark:
 * The shell expands $? to be the numeric exit status of the last executed
 * command (and evidently it is a signed 8 bit quanitity.)
 *
 *
 * A nifty shell trick involving exit status codes as a failure indicator:
 *
 *      $ ./exitstatus 0 && echo no failure
 *      no failure
 *
 *      $ ./exitstatus 1 && echo no failure
 *           (nothing will be printed, i.e. `echo` command never runs)
 *
 *      $ ./exitstatus 0 || echo something failed
 *           (nothing will be printed, i.e. `echo` command never runs)
 *
 *      $ ./exitstatus 1 || echo something failed
 *      something failed
 */
int main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("usage: %s exitstatus\n", argv[0]);
        return -1;
    }

    int status = atoi(argv[1]);

    // Explicit exit with status code
    exit(status);

    // Alternatively
    //return status;

    printf("This will never run.\n");

    return -1;
}
