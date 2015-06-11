#include <stdio.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    union {
        int x;
        int y;
        int z;
        int w;
    } record;

    record.z = 209;

    assert(record.x == 209);
    assert(record.y == 209);
    assert(record.z == 209);
    assert(record.w == 209);

    return 0;
}
