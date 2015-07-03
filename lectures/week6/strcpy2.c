#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Using `strcpy` vs `strcat`
 */
int main(int argc, char *argv[])
{
    char s[16];

    s[0] = '\0';
    strcpy(s, "The quick brown fox jumps over the lazy dog");

    printf("%s\n", s); 

    return 0;
}
