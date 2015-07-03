#include <stdio.h>
#include <stdlib.h>

/* Static Data (fixed size) - Global Constants & Variables */
const long constant = 42;
const char course[] = "CSC209";

long variable = 209;
long array[100];

/* Code */
void my_func(long func_param);

int main(int argc, char *argv[])
{
    /* Stack: local variables and function parameters */
    long local_var = 1;
    long local_var2 = 2;
    char *dynamic_data1, *dynamic_data2;

    printf("Local function arguments:\n");
    printf("    &argc           = 0x%lx\n", (unsigned long) &argc);
    printf("    &argv           = 0x%lx\n", (unsigned long) &argv);
    printf("\n");

    printf("Local variables (main):\n");
    printf("    &local_var      = 0x%lx\n", (unsigned long) &local_var);
    printf("    &local_var2     = 0x%lx\n", (unsigned long) &local_var2);
    printf("    &dynamic_data1  = 0x%lx\n", (unsigned long) &dynamic_data1);
    printf("    &dynamic_data2  = 0x%lx\n", (unsigned long) &dynamic_data2);
    printf("\n");

    my_func(local_var);

    // Allocate 32 MiB of dynamic memory, twice
    const int thirty_two_meg = 32 * (1 << 20);
    dynamic_data2 = (char *) malloc(thirty_two_meg);
    dynamic_data1 = (char *) malloc(thirty_two_meg);

    printf("Dynamic Data (heap allocated):\n");
    printf("    dynamic_data1   = 0x%012lx\n", (unsigned long) dynamic_data1);
    printf("    dynamic_data2   = 0x%012lx\n", (unsigned long) dynamic_data2);
    printf("           32 MiB   = 0x%12x\n", thirty_two_meg);
    printf("\n");

    // Free your dynamically allocated once you are done with it
    free(dynamic_data1);
    free(dynamic_data2);

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

    /*
    printf("Unused Logical Address Space:\n");
    unsigned long diff = (unsigned long) &local_var - (unsigned long) &variable;
    printf("\t&local_var - &variable = 0x%lx (%d GiB)\n", diff, diff >> 30);
    */

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
