#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    char course1[] = { 67,  83,  67,  50,  48,  57,    0  };
    char course2[] = { 'C', 'S', 'C', '2', '0', '9', '\0' };
    char course3[] = "CSC209";

    size_t len = sizeof (course1);
    assert (len == sizeof (course2));
    assert (len == sizeof (course3));

    printf("memcmp(course1, course2, len) = %d\n", memcmp(course1, course2, len));
    printf("memcmp(course1, course3, len) = %d\n", memcmp(course1, course3, len));
    printf("memcmp(course2, course3, len) = %d\n", memcmp(course2, course3, len));

    return 0;
}
