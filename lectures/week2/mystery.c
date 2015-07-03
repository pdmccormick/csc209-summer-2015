#include <stdio.h>

int main(int argc, char *argv[])
{
    int mystery = 0x435343;
    long addr_mystery = (long) &mystery;

    printf("mystery         = 0x%x\n", mystery);
    printf("addr_mystery    = 0x%lx\n", addr_mystery);

    return 0;
}

