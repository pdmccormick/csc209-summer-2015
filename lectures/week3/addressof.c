#include <stdio.h>

/* Global variables (declared outside of the scope of a function) */
char global_var = 100;
unsigned long addr_global_var = (unsigned long) 0;

int main(int argc, char *argv[])
{
    printf("global_var      = %d\n", global_var);
    printf("addr_global_var = 0x%lx\n\n", addr_global_var);

    /*
    printf("sizeof (global_var)       = %ld\n", sizeof (global_var));
    printf("sizeof (addr_global_var)  = %ld\n\n", sizeof (addr_global_var));
    */

    /*
    char local_var = -100;
    long addr_local_var = (long) 0;

    printf("local_var       = %d\n", local_var);
    printf("addr_local_var  = 0x%lx\n", addr_local_var);
    */

    return 0;
}
