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
     int k = 0;
     int *p = &k;
     short *q = ( short *) &k;
     char *r = ( char *) &k;

    printf("&k = %p\n", &k);
    printf("&p = %p\n", &p);
    printf("&q = %p\n", &q);
    printf("&r = %p\n", &r);
    printf("\n");

    printf("p  = %p\n", p);
    printf("q  = %p\n", q);
    printf("r  = %p\n", r);
    printf("\n");

    show_hex(&k, sizeof (k));

    *p = 0xFEDCBA98;
    show_hex(&k, sizeof (k));

    *q = 0x7654;
    show_hex(&k, sizeof (k));

    *r = 0x32;
    show_hex(&k, sizeof (k));

    return 0;
}
