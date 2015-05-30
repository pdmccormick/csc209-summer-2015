#include <stdio.h>

int main(int argc, char *argv[])
{
    /* `x` is a variable name that refers to an 8 bit, signed integer value. */
    char x;
    
    /* That variable requires 1 byte of storage, and will be given an address
     * somewhere on the stack.
     *
     * The _value_ of a variable will be placed in memory at the variables'
     * _address_.
     *
     * In this case, `addr_x` is also just a variable containing 64 bit
     * integers (8 bytes), and those 8 bytes also live somewhere in memory
     * (i.e. it has an address.)
     */
    unsigned long addr_x = (unsigned long) &x;

    x = 21;
    printf("x                = %d\n", x);
    printf("addr_x           = 0x%lx\n\n", (unsigned long) addr_x);

    /* We can declared a pointer to a type (`char` in this example) by adding a
     * `*` after the type and before the variable name: */
    char *x_ptr;

    /* A pointer is just a numeric variable that stores as address. In this
     * case, we set the _value_ of the pointer to be the _address_ where
     * another variable, `x`, is stored. */
    x_ptr = &x;

    /* On a 64 bit system, a pointers' value will be a 64 bit memory address
     * too, so the _value_ of `x_ptr` will be the same as the value of
     * `addr_x`, because they both were assigned the address of the variable
     * `x`: */
    printf("x_ptr            = 0x%lx\n\n", (unsigned long) x_ptr);

    /* Keep in mind that, as an integer valued variable and just like `addr_x`,
     * `x_ptr` requires a several number of bytes to store, and also has itself
     * an address. */

    /* Even though the values of `x_ptr` and `addr_x` were the same as integers
     * representing memory addresses, the pointer `x_ptr` also carries around
     * that type information, `char` in this example.
     *
     * By using the dereference star `*` operator on a pointer, we ask the C
     * language & compiler to go ahead and use the pointer value to actually
     * access the memory whose address it is pointing to:
     */
    char deref = *x_ptr;
    printf("*x_ptr           = %d\n", deref);

    /* Since `x_ptr` contains the address of `x`, by looking up that address we
     * will retrieve the current 8 bit char value stored there. */

    /* Instead of dereferencing a pointer to access the value in memory it
     * points to (using the `*` operator on the right-hand side of an
     * assignment, in the context of an expression), we can use it on the left
     * hand side of an assignment, and actually effect a change to the memory
     * location whose address the pointer stores:
     */
    *x_ptr = 42;
    printf("*x_ptr           = %d\n", *x_ptr);

    /* After using the memory address value of a pointer variable to lookup
     * that address and change the contents of 1 byte of memory, if the address
     * of that byte of memory was also the same address that another local
     * variable was being stored at, what has happened to the value of that
     * local variable? */
    printf("x                = %d\n", x);

    return 0;
}
