/**
 * CSC209 Chat Server
 * ------------------
 */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

#include "defs.h"
#include "util.h"
#include "command.h"
#include "client.h"
#include "channel.h"

static int server_setup(Server *server, char *hostname, int port);
static int server_run(Server *server);
static int server_accept_new_client(Server *server);
static void server_handle_client_input(Client *client, char *msg, int msg_len);

static Server global_server = {};

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "usage: %s hostname port\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *hostname = argv[1];
    int port = atoi(argv[2]);

    if (!server_setup(&global_server, hostname, port)) {
        exit(EXIT_FAILURE);
    }

    if (!server_run(&global_server)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


/**
 * Setup the server instance.
 *
 * Return 1 (true) on success, otherwise 0 (false) on failure. This function
 * should return 0 immediately if any of the system calls return an error.
 */
static int server_setup(Server *server, char *hostname, int port)
{
    // TODO FIXME
    /* 1) Create TCP/IPv4 socket, saving it to `server->sockfd` */

    /* 2) Use `setsockopt` to enable SO_REUSEADDR */

    /* 3) Use `gethostbyname` to lookup the address of `hostname` */

    /* 4) Populate `server->addr` (which is of type `struct sockaddr_in`) with
     * the resolved hostname and port. */

    /* 5) Bind the socket FD to the bound address */

    /* 6) Setup the socket FD for listening */

    /* 7) Zero out the `server->all_sock_fds` file descriptor set, add
     * `server->sockfd` to it and set `server->max_fd` accordingly. */

    printf("Ready for connections to %s:%d\n",
            inet_ntoa(server->addr.sin_addr),
            ntohs(server->addr.sin_port));

    return 1;
}


/**
 * The main server event loop using select()
 *
 * Return 0 (false) on failure, 1 (true) otherwise (although under normally conditions this
 * function will never return.)
 */
static int server_run(Server *server)
{
    // TODO FIXME Put the following inside of an infinite while(1) loop
    //while (1) {
        /* 1) Create a fresh new local variable for the read FD set, and copy
         * `server->all_sock_fds` to it */

        /* 2) Issue select() call with correct FD upper bound and read set */

        /* 3) Check for read activity on the server listening socket. If there
         * is, call `server_accept_new_client`. */

        /* 4a) Iterate through each of `server->clients`, and for each connected
         * client, check for read activity.
         */

        /* 4b) If a clients' descriptor is ready to read, issue a read() call
         * with a 4096 byte local variable buffer.
         */

        /* 4c) Call `server_handle_client_input` with the client, buffer and bytes read. */
    //}

    return 0;
}


/**
 * Accepts new client connections on the server socket.
 *
 * This function should accept() new connections, and populate a `Client`
 * structure with all the relevant details, and make the client join the
 * "csc209" channel to start off.
 *
 * Returns 1 on successfully establishing a new client connection, otherwise 0.
 */
static int server_accept_new_client(Server *server)
{
    // TODO FIXME:
    /* 1) Call `client_new` to get a newly allocated `Client` structure */
    Client *client;

    /* 2) Call accept() in order to complete the client connection */

    /* 3) Make sure you copy in the socket file descriptor (`sockfd` field) and
     * address (`addr` field) to the new `Client`
     */

    /* 4) Check if the new descriptor is larger than `max_fd` in `server`, and
     * add it to the `all_sock_fds` set
     */

    /* 5) Use `client_printf` to send a welcome message to the client */

    /* 6) Use the `command_join` command to, by default, make new clients join
     * the "csc209" channel */

    printf("%s (@%s) connected\n", client_addrstr(client), client->nick);

    return 0;
}


/**
 * Handle input from a connected client.
 *
 * This function will distinguish between commands (those that begin with '/')
 * and regular chat messages (everything else.) For commands, it will call the
 * `command_*` handler functions (prototyped in `command.h` and implemented in
 * `command.c`) to perform the intended actions.
 */
static void server_handle_client_input(Client *client, char *msg, int msg_len)
{
    // Ensure that `msg` is a valid C-style string
    msg[msg_len] = '\0';

    // Call `strip_trailing_newlines` helper function
    strip_trailing_newlines(msg);

    // Ignore an empty message
    if (*msg == '\0') {
        return;
    }

    char *cmd_buf = strdup(msg);
    char *cmd, *args;
    if (parse_command(cmd_buf, &cmd, &args)) {
        // NB: This `printf` is only printed by the server process
        printf("%s (@%s): %s\n", client_addrstr(client), client->nick, msg);

        // Handle the currently defined commands
        if (strcmp(cmd, "help") == 0) {
            command_help(client);
        }
        else if (strcmp(cmd, "join") == 0) {
            command_join(client, args);
        }
        else if (strcmp(cmd, "nick") == 0) {
            command_nick(client, args);
        }
        else if (strcmp(cmd, "disconnect") == 0) {
            command_disconnect(client);
        }
        else if (strcmp(cmd, "channels") == 0) {
            command_channels(client);
        }
        else if (strcmp(cmd, "who") == 0) {
            command_who(client);
        }
        else {
            /* If you have an idea for a useful new command, you can add
             * additional handling here. */

            printf("%s (@%s): unrecognized command '%s'\n", client_addrstr(client), client->nick, cmd);
            client_printf(client, "! Unrecognized command '%s'\n", cmd);
        }
    }
    else {
        // TODO FIXME
        /* Since the user has transmitted a non-command chat message, broadcast
         * it to their current channel using the `channel_broadcast_printf`
         * function.
         *
         * You should format the broadcast so that messages look something like
         * the following:
         *
         *      astudent: hi everyone
         *      pdm: welcome to the channel!
         *      g5stdnt: hello world
         */
    }

    free(cmd_buf);
}
