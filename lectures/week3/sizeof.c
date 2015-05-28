#include <stdio.h>

int main(int argc, char *argv[])
{
    long var = 50;

    printf("sizeof (long)      = %ld\n", sizeof (long));
    printf("sizeof (var)       = %ld\n", sizeof (var));

    /*
    long array[4] = { 100, 200, 300, 400 };

    printf("sizeof (array[0])  = %ld\n", sizeof (array[0]));
    printf("sizeof (array)     = %ld\n", sizeof (array));

    int num_elems = -1;
    printf("# elements         = %d\n\n", num_elems);
    */

    /*
    char course1[] = "CSC209";
    printf("sizeof (course1)    = %ld\n", sizeof (course1));
    */

    return 0;
}
