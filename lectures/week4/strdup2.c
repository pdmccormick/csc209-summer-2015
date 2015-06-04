#include <stdio.h>
#include <string.h>

char *make_upper(char *str);

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("usage: %s argument\n", argv[0]);
        return -1;
    }

    printf("original  string : \"%s\"\n", argv[1]);

    char *str = make_upper(argv[1]);
    printf("uppercase string : \"%s\"\n", str);

    printf("original  string : \"%s\"\n", argv[1]);

    // Use of `strcmp` to compare strings; 0 return value indicates equality
    /*
    if (strcmp(str, argv[1]) == 0) {
        printf("\n");
        printf("Original and uppercase version are equal as strings.\n");
    }
    */

    return 0;
}

char *make_upper(char *input)
{
    int i;
    size_t len = strlen(input);
    char *output = input;

    for (i = 0; i < len; i++) {
        // If this character is a lower case letter, shift it to be upper
        if (output[i] >= 'a' && output[i] <= 'z') {
            output[i] = (output[i] - 'a') + 'A';
        }
    }

    return output;
}
