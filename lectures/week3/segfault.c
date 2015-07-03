#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int *null_ptr = NULL;

    // Dereference a NULL pointer
    int oops = *null_ptr;

    (void)oops;

    printf("How did we survive a crash?\n");
    return -1;
}
