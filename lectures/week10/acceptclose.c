#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("usage: %s port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);

    // Create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Bind to localhost & port
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port); 
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (bind(sockfd, (struct sockaddr *) &addr, sizeof (addr)) < 0) {
        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Prepare for new connections
    if (listen(sockfd, 128) < 0) {
        perror("listen");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    int num_client = 0;

    while (1) {
        // Block waiting for a new connection
        struct sockaddr_in client_addr;
        socklen_t addrlen = sizeof (client_addr);

        int clientfd = accept(sockfd, (struct sockaddr *) &client_addr, &addrlen);
        if (clientfd < 0) {
            perror("accept");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        // clientfd is now connected!
        num_client++;

        printf("Connection #%d from %s:%d\n",
                num_client,
                inet_ntoa(client_addr.sin_addr),
                ntohs(client_addr.sin_port));

        char buf[128];
        int msg_len = snprintf(buf, sizeof (buf), "Hello, you were client #%d\n", num_client);

        ssize_t written = write(clientfd, buf, msg_len);

        // This won't always be the case for streaming sockets...
        assert (written == msg_len);

        close(clientfd);
    }

    // Wait for keypress...
    printf("bind complete, now waiting\n");
    fgetc(stdin);

    printf("done\n");

    close(sockfd);

    return EXIT_SUCCESS;
}
