#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <netdb.h>
#include <arpa/inet.h>

#define MAX_CLIENTS     (FD_SETSIZE)

static void handle_accept(int sockfd, int client_fds[]);
static int handle_client_readiness(int num, int clientfd);

int main(int argc, char *argv[])
{
    int i;

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

    // Initialize client FD array to all -1 (indicating unused entry)
    int client_fds[MAX_CLIENTS];
    for (i = 0; i < MAX_CLIENTS; i++) {
        client_fds[i] = -1;
    }

    while (1) {
        // Setup the read set with the listening FD and any connected clients
        fd_set readfds;

        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);

        int max_fd = sockfd;
        for (i = 0; i < MAX_CLIENTS; i++) {
            if (client_fds[i] == -1) {
                continue;
            }

            // Add client socket FD to set
            FD_SET(client_fds[i], &readfds);

            if (client_fds[i] > max_fd) {
                max_fd = client_fds[i];
            }
        }

        // Call select
        int rc = select(max_fd + 1, &readfds, NULL, NULL, NULL);
        if (rc < 0) {
            switch (errno) {
            case EINTR:
                fprintf(stderr, "select() returned EINTR, continuing\n");
                continue;

            default:
                perror("select");
                exit(EXIT_FAILURE);
            }
        }

        // Are there new connections on the listening socket?
        if (FD_ISSET(sockfd, &readfds)) {
            handle_accept(sockfd, client_fds);
        }

        for (i = 0; i < MAX_CLIENTS; i++) {
            // No client FD in this entry
            if (client_fds[i] == -1) {
                continue;
            }

            // select did not indicate readiness fro this FD
            if (!FD_ISSET(client_fds[i], &readfds)) {
                continue;
            }

            // Handle client FD
            client_fds[i] = handle_client_readiness(i, client_fds[i]);
        }
    }

    close(sockfd);

    return EXIT_SUCCESS;
}

/**
 * Handle a pending client connection on `sockfd`, finding a suitable location
 * in `client_fds` to store the descriptor.
 */
static void handle_accept(int sockfd, int client_fds[])
{
    int i;

    struct sockaddr_in client_addr;
    socklen_t addrlen = sizeof (client_addr);

    int fd = accept(sockfd, (struct sockaddr *) &client_addr, &addrlen);
    if (fd < 0) {
        perror("accept");
        return;
    }

    // Find an entry in the `client_fds` array
    for (i = 0; i < MAX_CLIENTS; i++) {
        if (client_fds[i] == -1) {
            break;
        }
    }

    if (i == MAX_CLIENTS) {
        fprintf(stderr, "Too many clients, closing new connection...\n");
        close(fd);
    }

    client_fds[i] = fd;

    fprintf(stderr, "Client #%d connected from %s:%d\n",
            i,
            inet_ntoa(client_addr.sin_addr),
            ntohs(client_addr.sin_port));
}

/**
 * Handle activity on the client socket descriptor
 */
static int handle_client_readiness(int num, int clientfd)
{
    char buf[512 + 1];
    ssize_t bytes_read = read(clientfd, buf, sizeof (buf) - 1);

    if (bytes_read < 0) {
        perror("read");
        return -1;
    }
    else if (bytes_read == 0) {
        // A `read` return value of 0 indicates end-of-stream
        fprintf(stderr, "Client #%d disconnected\n", num);
        return -1;
    }
    else {
        // Ensure buf is a C string (we were careful about the sizing above)
        buf[bytes_read] = '\0';

        // Strip out last newline for printing convenience
        char *nl = strrchr(buf, '\n');
        if (nl != NULL) {
            *nl = '\0';
        }

        fprintf(stdout, "Client #%d said: %s\n", num, buf);
    }

    return clientfd;
}
