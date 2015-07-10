#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "signal2str.h"
#include "waithelper.h"

int main(int argc, char *argv[])
{
    pid_t child = fork();
    if (child < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (child == 0) {
        // Child
        printf("child: attempting to dereference a NULL pointer...\n");
        
        int *p = (int *) NULL;
       
        // Geronimo! 
        *p = 209;
    }
    else {
        // Parent

        // Reap child
        wait_for_child(child);
    }

    return EXIT_SUCCESS;
}
