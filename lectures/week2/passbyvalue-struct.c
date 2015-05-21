#include <stdio.h>

struct Course {
    int code;
    int num_enrolled;
};

void add_spots(struct Course csc209);

int main(int argc, char *argv[])
{
    struct Course csc209;

    csc209.code = 209;
    csc209.num_enrolled = 100;

    printf("before call num_enrolled = %d\n", csc209.num_enrolled);
    add_spots(csc209);
    printf("before call num_enrolled = %d\n", csc209.num_enrolled);

    return 0;
}

void add_spots(struct Course csc209)
{
    // Add 50 more spots!
    csc209.num_enrolled += 50;

    printf("\tincreased enrollment to %d\n", csc209.num_enrolled);
}

