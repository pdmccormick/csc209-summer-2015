#include <stdio.h>
#include <string.h>
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

#   if 0
    // Enable the SO_REUSEADDR option on sockfd
    int optval = 1; // Boolean true

    if (setsockopt(
                sockfd,
                SOL_SOCKET,
                SO_REUSEADDR,
                (void *) &optval,
                sizeof (optval)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
#   endif

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

    fprintf(stderr, "Listening for connections on %s:%d\n",
            inet_ntoa(addr.sin_addr),
            ntohs(addr.sin_port));

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

        fprintf(stderr, "Connection #%d from %s:%d\n",
                num_client,
                inet_ntoa(client_addr.sin_addr),
                ntohs(client_addr.sin_port));

        int connected = 1;

        while (connected) {
            char buf[512 + 1];
            ssize_t bytes_read = read(clientfd, buf, sizeof (buf) - 1);

            if (bytes_read < 0) {
                perror("read");
                connected = 0;
            }
            else if (bytes_read == 0) {
                // A `read` return value of 0 indicates end-of-stream
                fprintf(stderr, "Client %s:%d disconnected\n",
                        inet_ntoa(client_addr.sin_addr),
                        ntohs(client_addr.sin_port));
                connected = 0;
            }
            else {
                // Ensure buf is a C string (we were careful about the sizing above)
                buf[bytes_read] = '\0';

                // Strip out last newline for printing convenience
                char *nl = strrchr(buf, '\n');
                if (nl != NULL) {
                    *nl = '\0';
                }

                fprintf(stdout, "Client %s:%d said: %s\n",
                        inet_ntoa(client_addr.sin_addr),
                        ntohs(client_addr.sin_port),
                        buf);
            }
        }

        close(clientfd);
    }

    close(sockfd);

    return EXIT_SUCCESS;
}
