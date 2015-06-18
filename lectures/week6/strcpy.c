#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Using `strcpy` vs `strcat`
 */
int main(int argc, char *argv[])
{
    char s[1024];

    // strcat
    s[0] = '\0';
    strcat(s, "Hello ");
    strcat(s, "CSC209!");
    printf("Using `strcat`: %s\n", s);
    
    // strcpy
    s[0] = '\0';
    strcpy(s, "Hello ");
    strcpy(s, "CSC209!");
    printf("Using `strcpy`: %s\n", s);

    return 0;
}
