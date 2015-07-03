#include <stdio.h>
#include <assert.h>

void enum1_unnamed()
{
    enum {
        FOO,
        BAR,
        BAZ,
    };

    int x = FOO;
    int y = BAR;
    int z = BAZ;

    assert(x == 0);
    assert(y == 1);
    assert(z == 2);
}

void enum2_named()
{
    enum Friends {
        FOO,
        BAR,
        BAZ,
    };

    enum Friends x = FOO;
    enum Friends y = BAR;
    enum Friends z = BAZ;

    assert(x == 0);
    assert(y == 1);
    assert(z == 2);

    enum Friends w = 10;
    assert(w == 10);
    printf("%d\n", w);
}

void enum3_switch()
{
    enum Friends {
        FOO,
        BAR,
        BAZ,
    };

    enum Friends x = FOO;

    switch (x) {
    case FOO:
        printf("foo!\n");
        break;
    }

}

int main(int argc, char *argv[])
{
    enum1_unnamed();
    enum2_named();
    enum3_switch();

    return 0;
}
