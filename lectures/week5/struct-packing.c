#include <stdio.h>
#include <stddef.h>

struct Align1 {
    char x;
    char y;
    char z;
    char w;
};

/* Change at least one `char` field from Align1 to a `short` field */
struct Align2 {
    char x;
    short y; // *
    char z;
    char w;
};

struct Align4 {
    char x;
    short y;
    int z; // *
    char w;
};

struct Align8 {
    long x; // *
    short y;
    int z;
    char w;
};

void print_offsets(void *s, void *a, size_t len_a, void *b, size_t len_b, void *c, size_t len_c, void *d, size_t len_d);

// This is a C pre-processor macro that will save us some repetition later
#define PRINT_MACRO(var)                \
            print_offsets(&(var),       \
            &(var).x, sizeof ((var).x), \
            &(var).y, sizeof ((var).y), \
            &(var).z, sizeof ((var).z), \
            &(var).w, sizeof ((var).w))

int main(int argc, char *argv[])
{
    struct Align1 a1;
    struct Align2 a2;
    struct Align4 a4;
    struct Align8 a8;

    printf("1 byte alignment:\n");
    PRINT_MACRO(a1);

    /* Using the macro saves up from having to copy, paste and modify the following line 4 times:
    print_offsets(&a1, &a1.x, &a1.y, &a1.z, &a1.w);
    */
    printf("\n");

    printf("2 byte alignment:\n");
    PRINT_MACRO(a2);
    printf("\n");

    printf("4 byte alignment:\n");
    PRINT_MACRO(a4);
    printf("\n");

    printf("8 byte alignment:\n");
    PRINT_MACRO(a8);
    printf("\n");


    return 0;
}

void print_offsets(void *s, void *x, size_t len_x, void *y, size_t len_y, void *z, size_t len_z, void *w, size_t len_w)
{
    ptrdiff_t base = (ptrdiff_t) s;

    ptrdiff_t offs_x = (ptrdiff_t) x - base;
    ptrdiff_t offs_y = (ptrdiff_t) y - base;
    ptrdiff_t offs_z = (ptrdiff_t) z - base;
    ptrdiff_t offs_w = (ptrdiff_t) w - base;

    printf("  x  offs=%2lu length=%lu\n", offs_x, len_x);
    printf("  y  offs=%2lu length=%lu\n", offs_y, len_y);
    printf("  z  offs=%2lu length=%lu\n", offs_z, len_z);
    printf("  w  offs=%2lu length=%lu\n", offs_w, len_w);
}
