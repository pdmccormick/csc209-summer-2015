#include <stdio.h>

int main(int argc, char *argv[])
{
    long array[4] = { 100, 200, 300, 400 };

    /* Show the _value_ of each array element: */
    printf("array[0]     = %ld\n", array[0]);
    printf("array[1]     = %ld\n", array[1]);
    printf("array[2]     = %ld\n", array[2]);
    printf("array[3]     = %ld\n", array[3]);
    printf("\n");

    /* Show the _address_ where each array element is stored: */
    printf("&array       = 0x%lx\n", (unsigned long) &array);
    printf("&array[0]    = 0x%lx\n", (unsigned long) &array[0]);
    printf("&array[1]    = 0x%lx\n", (unsigned long) &array[1]);
    printf("&array[2]    = 0x%lx\n", (unsigned long) &array[2]);
    printf("&array[3]    = 0x%lx\n", (unsigned long) &array[3]);
    printf("\n");
    /* 
     * A few important facts: 
     * 
     * 1. The address of the array variable itself is same as the address of
     * the first element.
     *
     * 2. There is no extra memory space allocated for any other information
     * (i.e. there is no built-in array size or length)
     *
     * 3. Each array element takes a certain number of bytes to store, `sizeof
     * (array[0]) == sizeof (long) == 8` in this case, so each successive
     * element is 8 bytes after the last.
     */

    /* A pointer-type variable simply holds a number (which happens to be a
     * memory address.) */
    long *array_ptr = (long *) &array;
    printf("array_ptr    = 0x%lx\n", (unsigned long) array_ptr);

    /* Using the dereference star (*) operator, we modify the memory where the
     * first array element is being stored: */
    *array_ptr = 101;
    printf("array[0]     = %ld\n", array[0]);
    printf("\n");

    /* A pointer can also be dereferenced using the array bracket [ ] syntax: */
    array_ptr[0] = 102;
    printf("array[0]     = %ld\n", array[0]);
    printf("\n");

    /* The following memory addresses are all the same: */
    printf("&array[1]     = 0x%lx\n", (unsigned long) &array[1]);
    printf("&array_ptr[1] = 0x%lx\n", (unsigned long) &array_ptr[1]);
    printf("array_ptr + 1 = 0x%lx\n", (unsigned long) (array_ptr + 1));

    /*
     * The resulting memory address value of adding something to a pointer will
     * see that addition scaled by the sizeof the type of the pointer.
     *
     * So if the value of `array_ptr` (i.e. the memory address it is pointing
     * too) were 0x1000, then the address value of C expression `array_ptr + 1`
     * would be:
     *
     *  array_ptr + 1 === 0x1000 + (1 * sizeof (*array_ptr))
     *                === 0x1000 + (1 * sizeof (long))
     *                === 0x1000 + 8
     *                === 0x1008
     *
     * And similarly,
     *
     *  array_ptr + 2 === 0x1010 (that's 0x1000 plus decimal 16, which is hex 0x10)
     * 
     * The general rule is this:
     *
     *      array_ptr[i] === *(array_ptr + i)
     */

    return 0;
}
