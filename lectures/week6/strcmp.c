#include <stdio.h>
#include <string.h>

void show_strcmp(const char *s1, const char *s2)
{
    int rc;

    rc = strcmp(s1, s2);

    printf("strcmp(\"%s\", \"%s\") = %d\n", s1, s2, rc);
}

int main(int argc, char *argv[])
{
    show_strcmp("CSC209", "CSC209");
    show_strcmp("CSCB09", "CSC209");
    show_strcmp("CSC209", "CSC309");

    return 0;
}
