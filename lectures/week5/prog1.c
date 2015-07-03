#include <stdio.h>

// Uncomment the following line to avoid the warning
//void do_hello();

int main(int argc, char *argv[])
{
    printf("main\n");
    do_hello();
    return 0;
}

void do_hello(void)
{
    printf("hello\n");
}
