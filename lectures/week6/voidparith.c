#include <stdio.h>
#include <stddef.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    int i;
    const int fake_addr = 0x1000;

    printf("sizeof void == %zu\n", sizeof (void));

    // Pointer arithmetic on a `void *`
    void *vp = (void *) (ptrdiff_t) fake_addr;
    for (i = 0; i < 10; i++) {
        printf("vp + %d == %p\n", i, vp + i);

        int *vp_plus_i = (int *) (fake_addr + (i * sizeof (*vp)));
        assert ((vp + i) == vp_plus_i);
    }
    printf("\n");

    return 0;
}
