#include <stdio.h>

int main(int argc, char *argv[])
{
    long var = 50;
    long array[4] = { 100, 200, 300, 400 };

    printf("sizeof (array[0])  = %ld\n", sizeof (array[0]));
    printf("sizeof (array)     = %ld\n", sizeof (array));

    int num_elems = sizeof (array) / sizeof (array[0]);
    printf("# elements         = %d\n", num_elems);

    return 0;
}

