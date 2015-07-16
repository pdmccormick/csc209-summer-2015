#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("usage: %s hostname port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *hostname = argv[1];
    int port = atoi(argv[2]);

    // Lookup hostname
    struct hostent *hp = gethostbyname(hostname);

    if (hp == NULL) {
        fprintf(stderr, "%s: name not found\n", hostname);
        exit(EXIT_FAILURE);
    }

    // Setup server address
    struct sockaddr_in addr;
    struct in_addr *in4 = (struct in_addr *) hp->h_addr_list[0];

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port); 
    addr.sin_addr = *in4;

    printf("Connecting to %s on port %d\n",
        inet_ntoa(addr.sin_addr),
        port);

    /* Flush the file stream stdout wrapper here because later we are doing a
     * raw file descriptor write against it
     */
    fflush(stdout);

    // Create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Attempt to connect
    if (connect(sockfd, (struct sockaddr *) &addr, sizeof (addr)) < 0) {
        perror("connect");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    char buf[128];
    int msg_len = snprintf(buf, sizeof (buf),
            "GET / HTTP/1.1\r\n"
            "Host: %s\r\n"
            "Connection: close\r\n"
            "\r\n",
            hostname);

    ssize_t written = write(sockfd, buf, msg_len);
    assert (written == msg_len);

    // Read from sockfd and write to stdout
    while (1) {
        ssize_t bytes_read = read(sockfd, buf, sizeof (buf));

        if (bytes_read < 0) {
            perror("read");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        else if (bytes_read == 0) {
            break;
        }

        assert (write(STDOUT_FILENO, buf, bytes_read) == bytes_read);
    }

    close(sockfd);

    return EXIT_SUCCESS;
}
