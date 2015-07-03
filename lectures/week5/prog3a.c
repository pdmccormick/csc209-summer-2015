#include <stdio.h>

extern int flag;

void do_hello();

int main(int argc, char *argv[])
{
    printf("main  flag=%d\n", flag);

    flag = 2;

    do_hello();

    printf("main  flag=%d\n", flag);

    return 0;
}
