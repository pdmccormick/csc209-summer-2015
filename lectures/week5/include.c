/**
 * include.c: see the pre-processor file inclusion mechanism in action
 *
 * Run this example not by compiling, but by running the C pre-processor
 * (`cpp`) on it directly, as in:
 *
 *      $ cpp -C include.c
 *
 *  Also try this without the `-C` option and you will notice that the
 *  pre-processor strips away the comments from this file.
 */

/* Next we will use the preprocessor to bring in the contents of `header.h`: */
#include "header.h"

/* Back in `include.c` again, continuing on... */
int main(int argc, char *argv[])
{
    return 0;
}
