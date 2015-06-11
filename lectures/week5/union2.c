#include <stdio.h>

/**
 * Prints the individual bytes (from low to high address) of the memory pointed
 * to by `addr`.
 */
void show_hex(void *addr, size_t len)
{
    printf("%p  ", addr);

    int i;
    unsigned char *bytes = (unsigned char *) addr;
    for (i = 0; i < len; i++) {
        printf("%02x ", bytes[i]);
    }

    printf("\n");
}


int main(int argc, char *argv[])
{
    union {
        int p;
        short q;
        char r;
    } u = {};

    printf("sizeof (u) = %lu\n", sizeof (u));
    show_hex(&u, sizeof (u));

    u.p = 0xFEDCBA98;
    show_hex(&u, sizeof (u));

    u.q = 0x7654;
    show_hex(&u, sizeof (u));

    u.r = 0x32;
    show_hex(&u, sizeof (u));

    return 0;
}
