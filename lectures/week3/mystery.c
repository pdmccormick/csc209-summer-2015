#include <stdio.h>

int main(int argc, char *argv[])
{
    /* This variable occupies 4 bytes of memory somewhere, and at the address
     * where it lives, those 4 bytes contain its stored value, which appears to
     * be a meaningless number */
    int mystery = 0x435343;

    /* It has both a value (of a particular type, 32-bit signed integer), and
     * an address where it lives: */
    printf("Mystery 32 bit integer:\n");
    printf("  mystery  = 0x%x\n", mystery);
    printf("  &mystery = 0x%lx\n", (unsigned long) &mystery);
    printf("\n");

    /* If we take a pointer to the very same address, but of a smaller type (16
     * bit signed integer), we can treat those very same 4 bytes representing a
     * single value instead as 4 bytes representing two values, each of which
     * is only 2 bytes. */
    short *s = (short *) &mystery;
    printf("Mystery 16 bit short's:\n");
    printf("  s[0]     = 0x%x\n", s[0]);
    printf("  s[1]     = 0x%x\n", s[1]);
    printf("\n");

    /* We can go a step further and inspect each individual byte, treating the
     * 4 bytes as four separate values: */
    unsigned char *c = (unsigned char *) &mystery;
    printf("Mystery 8 bit char's:\n");
    printf("  c[0]     = 0x%x\n", c[0]);
    printf("  c[1]     = 0x%x\n", c[1]);
    printf("  c[2]     = 0x%x\n", c[2]);
    printf("  c[3]     = 0x%x\n", c[3]);
    printf("\n");

    /* In all these cases, we are looking at the exact same memory address,
     * just slicing it in different ways.
     *
     * What if the value that appeared to be a meaningless number, however,
     * turned out to represent something else? What if we displayed the char's
     * not as 8 bit decimal numbers, but as 8 bit ASCII characters?
     */
    printf("Mystery 8 bit ASCII char's:\n");
    printf("  c[0]     = '%c'\n", c[0]);
    printf("  c[1]     = '%c'\n", c[1]);
    printf("  c[2]     = '%c'\n", c[2]);
    printf("  c[3]     = '%c'\n", c[3]);
    printf("\n");

    /* In fact, this looks like it could be a C-style string, which consists of
     * zero or more ASCII characters followed by a NUL byte (integer 0): */
    printf("C-style NUL-terminated string:\n");
    char *str = (char *) &mystery;
    printf("  str      = \"%s\"\n", str);
    printf("\n");

    /* What if we go and change one of the bytes directly, how does that affect
     * the others? */
    c[2] -= 10;

    printf("Changing just 1 byte affects other representations:\n");
    printf("  s[1]     = 0x%x\n", s[1]);
    printf("  str      = \"%s\"\n", str);
    printf("  mystery  = 0x%x\n", mystery);
    printf("\n");

    /* What if we change 2 bytes together at once? */
    s[0] -= 0x2311;

    printf("Changing 2 bytes at once:\n");
    printf("  c[0]     = 0x%x\n", c[0]);
    printf("  c[1]     = 0x%x\n", c[1]);
    printf("  str      = \"%s\"\n", str);
    printf("  mystery  = 0x%x\n", mystery);
    printf("\n");


    /* Now it's your turn: here is an even longer 64 bit mystery integer...
     * what would it look like as 2 int's, 4 short's, or 8 char's? What about
     * as a string? */
    unsigned long mystery2 = 0x393032435343ul;

    /* This line suppress the "unused variable" warning: use `mystery2` in some
     * way, and then delete this line. */
    (void)mystery2;

    return 0;
}
