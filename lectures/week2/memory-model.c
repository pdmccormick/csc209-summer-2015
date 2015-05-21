#include <stdio.h>

const long constant = 42;
const char *course = "CSC209";

long variable = 209;
long array[100];

void my_func(long func_param);

int main(int argc, char *argv[])
{
    long local_var = 1;
    long local_var2 = 2;

    printf("Local function arguments:\n");
    printf("\t&argc       = 0x%lx\n", (long) &argc);
    printf("\t&argv       = 0x%lx\n", (long) &argv);
    printf("\n");

    printf("Local variables (main):\n");
    printf("\t&local_var2 = 0x%lx\n", (long) &local_var2);
    printf("\t&local_var  = 0x%lx\n", (long) &local_var);
    printf("\n");

    my_func(local_var);

    printf("Static Data (global variables):\n");
    printf("\t&variable   = 0x%012lx\n", (long) &variable);
    printf("\t&array      = 0x%012lx\n", (long) &array);
    printf("\n");

    printf("Static Data (global constants):\n");
    printf("\t&constant   = 0x%012lx\n", (long) &constant);
    printf("\t&course     = 0x%012lx\n", (long) &course);
    printf("\n");

    printf("Code:\n");
    printf("\t&my_func    = 0x%012lx\n", (long) &my_func);
    printf("\t&main       = 0x%012lx\n", (long) &main);
    printf("\n");

    return 0;
}

void my_func(long func_param)
{
    long func_local;

    printf("Local variables (my_func):\n");
    printf("\t&func_param = 0x%lx\n", (long) &func_param);
    printf("\t&func_local = 0x%lx\n", (long) &func_local);
    printf("\n");
}

