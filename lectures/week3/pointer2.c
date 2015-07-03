#include <stdio.h>

void add_21_by_value(int x);
void add_21_via_ptr(int *x_ptr);

/**
 * This example highlights the difference between passing the _value_ of a
 * local variable in to function as a parameter, and passing in as a parameter
 * a physical memory address reference to where a local variable is being
 * stored.
 */
int main(int argc, char *argv[])
{
    int x;

    /* Local variable `x` will NOT be modified by `add_21_by_value` */
    x = 21;
    printf("PASS BY VALUE:\n");
    printf("  main            BEFORE x = %d\n", x);
    printf("                        &x = 0x%lx\n", (unsigned long) &x);
    printf("\n");

    add_21_by_value(x);

    printf("  main            AFTER  x = %d\n", x);
    printf("\n\n");

    /* Local variable `x` will _not_ be modified by `add_21_by_value` */
    x = 21;
    printf("PASS BY REFERENCE (via a pointer):\n");
    printf("  main            BEFORE  x = %d\n", x);
    printf("                         &x = 0x%lx\n", (unsigned long) &x);
    printf("\n");

    add_21_via_ptr(&x);

    printf("  main            AFTER   x = %d\n", x);
    printf("\n");

    return 0;
}

void add_21_by_value(int x)
{
    printf("  add_21_by_value BEFORE x = %d\n", x);
    printf("                        &x = 0x%lx\n", (unsigned long) &x);
    printf("\n");

    /* Add 21 to the parameter. This only affects the value of a local
     * variable. */
    x += 21;


    printf("  add_21_by_value AFTER  x = %d\n", x);
    printf("\n");
}



void add_21_via_ptr(int *x_ptr)
{
    printf("  add_21_via_ptr  BEFORE *x_ptr = %d\n", *x_ptr);
    printf("                  BEFORE  x_ptr = %p\n", x_ptr);
    printf("                  BEFORE &x_ptr = %p\n", &x_ptr);
    printf("\n");

    /* Dereference the pointer and add 21 to the integer stored at that memory
     * location. */
    *x_ptr += 21;

    printf("  add_21_via_ptr  AFTER  *x_ptr = %d\n", *x_ptr);
    printf("                  AFTER   x_ptr = %p\n", x_ptr);
    printf("                  AFTER  &x_ptr = %p\n", &x_ptr);
    printf("\n");
}
