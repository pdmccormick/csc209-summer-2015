#include <stdio.h>

void do_work()
{
    printf("do_work\n");
}

int main(int argc, char *argv[])
{
    void (*func_ptr)(void);

    func_ptr = do_work;
    func_ptr();

    return 0;
}
