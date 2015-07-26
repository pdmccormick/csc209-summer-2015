/**
 * CSC209 Chat Server -- Client connection management
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <arpa/inet.h>

#include "client.h"
#include "channel.h"

/**
 * Sets up a new `Client` record associated with the server.
 *
 * Returns a pointer to a `Client` structure that has been registered with
 * `server`, otherwise NULL.
 */
Client *client_new(Server *server)
{
    assert (server != NULL);

    // Alert if we've reached the maximum
    if (server->num_clients >= SERVER_MAX_CLIENTS) {
        fprintf(stderr, "client_new ERROR: server already at maximum client limit!\n");
        return NULL;
    }

    // Allocate memory for the `Client` struct record
    Client *client = malloc(sizeof (*client));
    assert (client != NULL);

    memset(client, 0, sizeof (*client));

    client->server = server;

    // Find a free slot in the client list of the server
    int i;
    for (i = 0; i < SERVER_MAX_CLIENTS; i++) {
        if (server->clients[i] != NULL) {
            continue;
        }

        // We have found a free slot!
        server->clients[i] = client;
        server->num_clients++;

        client->server_clients = &server->clients[i];

        break;
    }

    // Sanity check in case the data structures have become corrupted
    if (i == SERVER_MAX_CLIENTS) {
        fprintf(stderr, "client_new INTERNAL FAILURE: server num_client %d < maximum %d but no free slot could be found!\n",
                server->num_clients, SERVER_MAX_CLIENTS);
        exit(EXIT_FAILURE);
    }

    // Give the client a default nickname
    char nick[128];
    snprintf(nick, sizeof (nick), "user%d", server->num_clients);
    client->nick = strdup(nick);

    return client;
}


/**
 * Initiate a write() to the clients' socket file descriptor.
 *
 * This helper function will ensure that all of the bytes you requested were
 * written.
 *
 * Returns 1 (true) on success, otherwise 0.
 */
int client_write(Client *client, const void *buf, size_t nbyte)
{
    assert (client != NULL);

    /**
     * The write() call may not be able to write all of the bytes we asked for.
     * In this case, we will repeatedly call it (with revised parameters) until
     * everything has been written.
     */
    const void *cur = buf;
    const void *end = buf + nbyte;
    size_t bytes_left = nbyte;

    while (bytes_left > 0 && cur < end) {
        ssize_t written = write(client->sockfd, cur, bytes_left);

        switch (written) {
        case -1:
            // Error on this socket
            perror("write");
            client_close(client);
            return 0;

        case 0:
            // Client has disconnected
            client_close(client);
            return 0;

        default:
            cur += written;
            bytes_left -= written;
        }
    }

    return 1;
}


/**
 * Use `printf` style format strings to send formatted text to a client.
 *
 * This is a variadic function, meaning that it can take a variable number of
 * arguments, just like the real `printf'. For example:
 *
 *      client_printf(client, "! Welcome to the CSC209 Chat Server\n");
 *
 *      char *nick = "foo";
 *      client_printf(client, " * @%s has left the channel\n", nick);
 *
 * Returns 1 (true) on success, otherwise 0.
 */
int client_printf(Client *client, const char *format, ...)
{
    assert (client != NULL);

#   define BUF_SIZE     4096
    static char buf[BUF_SIZE];

    va_list vl;
    va_start(vl, format);

    int buf_len = vsnprintf(buf, sizeof (buf), format, vl);

    return client_write(client, buf, buf_len);
}


/**
 * Close a current client connection.
 *
 *      TODO FIXME
 */
void client_close(Client *client)
{
    assert (client != NULL);

    printf("%s (@%s) connection closing\n", client_addrstr(client), client->nick);

    if (close(client->sockfd)) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    // TODO FIXME
    /* 1) Remove this clients' socket descriptor from the servers read set */

    /* 2) If this client is in a channel, remove them */

    /* Remove from server */
    assert (client->server->num_clients >= 1);
    assert (client->server_clients != NULL);
    assert (client->server_clients >= (Client **) &client->server->clients);
    assert (client->server_clients < ((Client **) &client->server->clients + sizeof (client->server->clients)));

    client->server->num_clients--;
    *client->server_clients = NULL;
    client->server_clients = NULL;

    free(client->nick);
    free(client);
}


/**
 * Returns a string-ified version of the client address, useful for printing server logs.
 *
 * Example: returns "127.0.0.1:53045"
 *
 * This returns a pointer into a static buffer that is reused across calls, so
 * NEVER attempt to modify the returned string, or keep the pointer longer than
 * a quick call to `printf`.
 */
const char *client_addrstr(Client *client)
{
    assert (client != NULL);

    // Static buffer, thus you CANNOT reuse this return value.
    static char buf[128];

    snprintf(buf, sizeof (buf), "%s:%d",
            inet_ntoa(client->addr.sin_addr),
            ntohs(client->addr.sin_port));

    return buf;
}
