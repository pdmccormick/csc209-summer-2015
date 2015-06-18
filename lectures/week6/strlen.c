#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char hello[] = { 'C', 'S', 'C', '2', '0', '9', '\0' };

    printf("hello          = \"%s\"\n", hello);
    printf("sizeof (hello) = %zu\n", sizeof (hello));
    printf("strlen(hello)  = %zu\n", strlen(hello));

    return 0;
}
