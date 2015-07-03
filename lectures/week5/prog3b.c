#include <stdio.h>

int flag = 1;

void do_hello(void)
{
    printf("hello flag=%d\n", flag);
    flag = 3;
}
