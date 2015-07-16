#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("usage: %s hostname\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *hostname = argv[1];

    struct hostent *hp = gethostbyname(hostname);

    if (hp == NULL) {
        perror("gethostbyname");
        exit(EXIT_FAILURE);
    }

    struct in_addr *in4 = (struct in_addr *) hp->h_addr_list[0];
    printf("address 0x%x\n", in4->s_addr);
   
    // This is very long winded... 
    printf("address %u.%u.%u.%u\n",
            (uint8_t) hp->h_addr_list[0][0],
            (uint8_t) hp->h_addr_list[0][1],
            (uint8_t) hp->h_addr_list[0][2],
            (uint8_t) hp->h_addr_list[0][3]);

    // `inet_ntoa` is much easier and less error prone
    printf("address %s\n", inet_ntoa(*in4));

    return EXIT_SUCCESS;
}
