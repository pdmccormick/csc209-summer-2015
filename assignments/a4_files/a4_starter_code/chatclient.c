/**
 * A simple TCP/IP chat client
 *
 * This application works very similarly to the `netcat` utility, but with two
 * small improvements. First, if the server sends you something while you are
 * typing a command, your input prompt is not trampled. Second, if the server
 * sends a "/prompt" command, your prompt text will be modified accordingly.
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

#include <readline/readline.h>

#include "util.h"

#define VT100_ERASE_LINE    "\33[2K\r"

/**
 * Global variable containing the current client state */
static struct {
    int connected;
    int sockfd;
    char *prompt;
} client_app;

static void handle_tty_input(char *line);
static int handle_net_read();


int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "usage: %s hostname port\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *hostname = argv[1];
    int port = atoi(argv[2]);

    client_app.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_app.sockfd < 0) {
        perror("socket");
        return EXIT_FAILURE;
    }

    // Lookup hostnmae
    struct hostent *hp = gethostbyname(hostname);

    if (hp == NULL) {
        fprintf(stderr, "%s: name not found\n", hostname);
        return EXIT_FAILURE;
    }

    // Setup address
    struct sockaddr_in addr;
    struct in_addr *in4 = (struct in_addr *) hp->h_addr_list[0];

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr = *in4;

    // Connect to server
    if (connect(client_app.sockfd, (struct sockaddr *) &addr, sizeof (addr)) < 0) {
        perror("connect");

        printf("Unable to connect to %s port %d\n",
            inet_ntoa(addr.sin_addr),
            port);

        close(client_app.sockfd);
        return EXIT_FAILURE;
    }

    printf("Connection to %s port %d succeeded!\n",
        inet_ntoa(addr.sin_addr),
        port);

    // Setup readline handler
    client_app.prompt = strdup("default-empty-prompt> ");
    rl_callback_handler_install(client_app.prompt, handle_tty_input);

    client_app.connected = 1;

    while (client_app.connected) {
        fd_set readfds;

        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        FD_SET(client_app.sockfd, &readfds);

        int rc = select(client_app.sockfd + 1, &readfds, NULL, NULL, NULL);

        if (rc < 0) {
            switch (errno) {
            case EINTR:
                // System call was interrupted, try again
                continue;

            default:
                perror("select");
                return EXIT_FAILURE;
            }
        }

        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            rl_callback_read_char();
        }

        if (FD_ISSET(client_app.sockfd, &readfds)) {
            if (handle_net_read() < 0) {
                client_app.connected = 0;
            }
        }
    }

    printf("\n");
    printf("Disconnecting from %s port %d...\n",
        inet_ntoa(addr.sin_addr),
        port);

    if (close(client_app.sockfd) < 0) {
        perror("close");
    }

    rl_callback_handler_remove();

    return EXIT_SUCCESS;
}


static void handle_tty_input(char *line)
{
    // The readline library returns NULL on EOF
    if (line == NULL) {
        client_app.connected = 0;
        return;
    }

    char msg[512];

    int msg_len = snprintf(msg, sizeof (msg), "%s\n", line);
    ssize_t bytes_written = write(client_app.sockfd, msg, msg_len);

    /* This may fail for legitimate reasons, but we will not handle those for
     * the time being.
     */
    assert (bytes_written == msg_len);

    rl_callback_handler_install(client_app.prompt, handle_tty_input);
}


static int handle_net_read()
{
    char buf[4096 + 1];
    ssize_t bytes_read = read(client_app.sockfd, buf, sizeof (buf) - 1);

    if (bytes_read < 0) {
        perror("read");
        return -1;
    }
    else if (bytes_read == 0) {
        // read() returning 0 indicates EOF
        return -1;
    }

    // Carefully NUL terminate the receive buffer
    buf[bytes_read] = '\0';
    strip_trailing_newlines(buf);

    char *cur = buf;
    char *next_line = NULL;

    while (1) {
        // Server may send multiple lines at once
        char *delim = strchr(cur, '\n');
        next_line = NULL;
        if (delim != NULL) {
            next_line = delim + 1;
            *delim = '\0';
            strip_trailing_newlines(cur);
        }

        printf(VT100_ERASE_LINE);

        // Check for server-sent commands
        char *cmd_buf = strdup(cur);
        char *cmd, *args;
        if (parse_command(cmd_buf, &cmd, &args)) {
            if (strcmp(cmd, "prompt") == 0) {
                char prompt[256];
                snprintf(prompt, sizeof (prompt), "%s> ", args);
                client_app.prompt = strdup(prompt);

                rl_callback_handler_install(client_app.prompt, handle_tty_input);
            }
        }
        else {
            // Print received message
            printf("%s\n", cur);
        }

        rl_forced_update_display();
        free(cmd_buf);

        cur = next_line;
        if (next_line == NULL || *next_line == '\0') {
            break;
        }
    }

    return 0;
}
