#include <stdio.h>
#include <stdlib.h>

void do_work1()
{
    printf("do_work1\n");
}

void do_work2()
{
    printf("do_work2\n");
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("usage: %s [1 | 2]\n", argv[0]);
        return -1;
    }

    int num = atoi(argv[1]);
    void (*func_ptr)(void);

    switch (num) {
    case 1:
        func_ptr = do_work1;
        break;

    case 2:
        func_ptr = do_work2;
        break;

    default:
        printf("usage: %s [1 | 2]\n", argv[0]);
        return -2;
    }

    func_ptr();

    return 0;
}
