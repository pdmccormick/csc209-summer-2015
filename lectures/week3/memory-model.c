#include <stdio.h>
#include <stdlib.h>

/* Static Data (fixed size) - Global Constants & Variables */
const long constant = 42;
const char course[] = "CSC209";

long variable = 209;
long array[100];

/* Code */
void my_func(long func_param);

/**
 * Show the memory addresse of various pieces of data in a given program
 */
int main(int argc, char *argv[])
{
    /* Stack: local variables and function parameters */
    long local_var = 1;
    long local_var2 = 2;

    printf("Local function arguments:\n");
    printf("    &argc           = 0x%lx\n", (unsigned long) &argc);
    printf("    &argv           = 0x%lx\n", (unsigned long) &argv);
    printf("\n");

    printf("Local variables (main):\n");
    printf("    &local_var      = 0x%lx\n", (unsigned long) &local_var);
    printf("    &local_var2     = 0x%lx\n", (unsigned long) &local_var2);
    printf("\n");

    my_func(local_var);

    printf("Unused Logical Address Space:\n");
    unsigned long diff = (unsigned long) &local_var - (unsigned long) &variable;
    printf("    &local_var - &variable\n");
    printf("                    = 0x%lx (%lu GiB)\n", diff, diff >> 30);
    printf("\n");

    printf("Dynamic Data (heap allocated):\n");
    printf("    ...\n");
    printf("\n");

    printf("Static Data (global variables):\n");
    printf("    &variable       = 0x%012lx\n", (unsigned long) &variable);
    printf("    &array          = 0x%012lx\n", (unsigned long) &array);
    printf("\n");

    printf("Static Data (global constants):\n");
    printf("    &constant       = 0x%012lx\n", (unsigned long) &constant);
    printf("    &course         = 0x%012lx\n", (unsigned long) &course);
    printf("\n");

    printf("Code:\n");
    printf("    &my_func        = 0x%012lx\n", (unsigned long) &my_func);
    printf("    &main           = 0x%012lx\n", (unsigned long) &main);
    printf("\n");

    return 0;
}

void my_func(long func_param)
{
    /* Stack: local variables and function parameters */
    long func_local;

    printf("Local variables (my_func):\n");
    printf("    &func_param     = 0x%lx\n", (unsigned long) &func_param);
    printf("    &func_local     = 0x%lx\n", (unsigned long) &func_local);
    printf("\n");
}
