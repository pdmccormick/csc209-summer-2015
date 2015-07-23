#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

static int socket_connect(char *hostname, int port);

/**
 * In two separate SSH sessions to the CDF server, run two netcat servers, each
 * on a different port, and leave them running:
 *
 *      $ /bin/nc -vlk localhost $PORT1
 *
 *      $ /bin/nc -vlk localhost $PORT2
 *
 * NB: You may wish to investigate a terminal multiplexer program
 * like `tmux` (`screen` is another) to help manage this
 * arrangement.
 *
 * Then run this example program (you will need a 3rd SSH connection to CDF):
 *
 *      $ ./run.sh dualclient1.c localhost $PORT1 localhost $PORT2
 *
 * Type something in the $PORT1 server window (followed by enter), and you
 * should it in the client. Do the same with the $PORT2 server, and similar
 * results follow.
 *
 * Type something again in the $PORT2 server, and hit enter. Why doesn't the
 * client show that? What if you then type something in the $PORT1 window? You
 * will see that message be received by the client, but then all the messages
 * original sent (but not yet received) from the $PORT2 server.
 */
int main(int argc, char *argv[])
{
    int i;

    if (argc != 5) {
        fprintf(stderr, "usage: %s hostname1 port1 hostname2 port2\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *hostname1 = argv[1];
    int port1 = atoi(argv[2]);

    char *hostname2 = argv[3];
    int port2 = atoi(argv[4]);

    // Make a connection to each server
    int fd1, fd2;

    if ((fd1 = socket_connect(hostname1, port1)) < 0) {
        fprintf(stderr, "Unable to connect to 1st host\n");
        exit(EXIT_FAILURE);
    }

    if ((fd2 = socket_connect(hostname2, port2)) < 0) {
        fprintf(stderr, "Unable to connect to 2nd host\n");
        exit(EXIT_FAILURE);
    }

    int fds[2] = { fd1, fd2 };

    // Read from each socket, one after the other
    while (fds[0] != -1 || fds[1] != -1) {
        char buf[512 + 1];
        ssize_t bytes_read;

        for (i = 0; i < 2; i++) {
            if (fds[i] < 0) {
                continue;
            }

            //printf("Calling read(%d, ...)\n", fds[i]);
            bytes_read = read(fds[i], buf, sizeof (buf) - 1);

            if (bytes_read < 0) {
                perror("read");
                close(fds[i]);
                fds[i] = -1;
            }
            else if (bytes_read == 0) {
                fprintf(stderr, "host %d (fd %d) went away\n", i, fds[i]);
                close(fds[i]);
                fds[i] = -1;
            }
            else {
                // NUL terminate to yield a C string
                buf[bytes_read] = '\0';

                printf("host%d said: %s\n", i, buf);
                //printf("read(%d, ...) returned %zd: %s\n", fds[i], bytes_read, buf);
            }
        }
    }

    return EXIT_SUCCESS;
}

static int socket_connect(char *hostname, int port)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("socket");
        return -1;
    }

    // Lookup hostnmae
    struct hostent *hp = gethostbyname(hostname);

    if (hp == NULL) {
        fprintf(stderr, "%s: name not found\n", hostname);
        return -1;
    }

    // Setup address
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr = *((struct in_addr *) hp->h_addr);

    printf("Connecting to %s on port %d\n",
        inet_ntoa(addr.sin_addr),
        ntohs(addr.sin_port));

    // Connect to server
    if (connect(sockfd, (struct sockaddr *) &addr, sizeof (addr)) < 0) {
        perror("connect");
        close(sockfd);
        return -1;
    }

    return sockfd;
}
