#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Gives us the hto*/nto* functions
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    // This _value_ is 16 bits in the hosts' network order
    uint16_t num16 = 0x1234;
    printf("16 bit (host)      : 0x%x\n", num16);

    // Convert from host to network order
    uint16_t num16_net = htons(num16);
    printf("16 bit (network)   : 0x%x\n", num16_net);

    // Convert from network back to host
    uint16_t num16_back = ntohs(num16_net);
    printf("16 bit (roundtrip) : 0x%x\n", num16_back);
    printf("\n");

    // This time with a 32 bit value
    uint32_t num32 = 0x12345678;

    printf("32 bit (host)      : 0x%x\n", num32);

    uint32_t num32_net = htonl(num32);
    printf("32 bit (network)   : 0x%x\n", num32_net);

    uint32_t num32_back = ntohl(num32_net);
    printf("32 bit (roundtrip) : 0x%x\n", num32_back);

    return EXIT_SUCCESS;
}
