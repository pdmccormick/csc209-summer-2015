#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("usage: %s string char\n", argv[0]);
        return -1;
    }

    char *str = argv[1];
    char *find_str = argv[2];

    if (strlen(find_str) != 1) {
        printf("ERROR: \"%s\" is greater than 1 character long!\n", find_str);
        return -1;
    }

    char find = find_str[0];

    char *first = strchr(str, find);
    char *last = strrchr(str, find);

    if (!first || !last) {
        printf("'%c' not found in \"%s\"\n", find, str);
        return -1;
    }

    printf("Searching for '%c' in \"%s\":\n", find, str);
    printf("  First at offset %tu: \"%s\"\n", first - str, first);
    printf("  Last  at offset %tu: \"%s\"\n", last - str, last);

    return 0;
}
