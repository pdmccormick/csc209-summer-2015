#include <stdio.h>

int array_product(int size, int array[]);

int main(int argc, char *argv[])
{
    int array[4] = { 1, 2, 3, 4 };

    printf("product of array elements = %d\n", array_product(4, array));

    return 0;
}

int array_product(int size, int array[])
{
    int i;
    int product = 1;

    for (i = 0; i < 4; i++) {
        product *= array[i];
    }

    return product;
}
