#include <stdio.h>

/**
 * Investigating the relationships between a value, a pointer to that value,
 * and a pointer to that pointer.
 */
int main(int argc, char *argv[])
{
    int i = 209;
    int *pi = &i;
    int **ppi = &pi;

    // Relationships among the value `i`
    printf("i         = %d\n", i);
    printf("*pi       = %d\n", *pi);
    printf("pi[0]     = %d\n", pi[0]);
    printf("**ppi     = %d\n", **ppi);
    printf("ppi[0][0] = %d\n", ppi[0][0]);
    printf("(*ppi)[0] = %d\n", (*ppi)[0]);
    printf("*(ppi[0]) = %d\n", *(ppi[0]));
    printf("\n");

    // Relationships among the value `pi`
    printf("pi         = %p\n", pi);
    printf("&i         = %p\n", &i);
    printf("*ppi       = %p\n", *ppi);
    printf("ppi[0]     = %p\n", ppi[0]);
    printf("&pi[0]     = %p\n", &pi[0]);
    printf("&ppi[0][0] = %p\n", &ppi[0][0]);
    printf("\n");

    // Relationships among the value `ppi`
    printf("ppi        = %p\n", ppi);
    printf("&pi        = %p\n", &pi);
    printf("&ppi[0]    = %p\n", &ppi[0]);
    printf("\n");

    return 0;
}
