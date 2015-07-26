/**
 * CSC209 Chat Server -- Channel management
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#include "defs.h"
#include "channel.h"
#include "client.h"

/**
 * Search for a named channel on the server.
 *
 * Returns a pointer to the `Channel` record if such a named channel exists,
 * otherwise NULL.
 */
Channel *channel_find(Server *server, char *name)
{
    assert (server != NULL);
    assert (name != NULL);

    // Iterate through all the channels on this server
    int i;
    for (i = 0; i < SERVER_MAX_CHANNELS; i++) {
        Channel *channel = server->channels[i];

        if (channel == NULL) {
            continue;
        }

        // Check the names of this record
        if (strcmp(name, channel->name) == 0) {
            // We found it!
            return channel;
        }
    }

    return NULL;
}


/**
 * Creates a new named channel on the server.
 *
 * Returns a pointer to the newly created `Channel` record if it could be
 * successfully created, otherwise NULL.
 */
Channel *channel_new(Server *server, char *name)
{
    assert (server != NULL);
    assert (name != NULL);

    // Proper usage check
    if (channel_find(server, name) != NULL) {
        fprintf(stderr, "channel_new INTERNAL FAILURE: channel \"%s\" already exists! Consider calling channel_find() first\n", name);
        exit(EXIT_FAILURE);
    }

    if (server->num_channels >= SERVER_MAX_CHANNELS) {
        fprintf(stderr, "channel_new ERROR: server already at maximum channel limit!\n");
        return NULL;
    }

    // Allocate memory and zero it out
    Channel *channel = malloc(sizeof (*channel));
    assert (channel != NULL);

    memset(channel, 0, sizeof (*channel));

    // Setup the channel structure
    channel->server = server;
    channel->name = strdup(name);

    // Find a free slot in the channel list
    int i;
    for (i = 0; i < SERVER_MAX_CHANNELS; i++) {
        if (server->channels[i] != NULL) {
            continue;
        }

        // Found a free slot
        server->channels[i] = channel;
        server->num_channels++;

        channel->server_channels = &server->channels[i];

        break;
    }

    if (i == SERVER_MAX_CHANNELS) {
        fprintf(stderr, "channel_new INTERNAL FAILURE: server num_channels %d < maximum %d but no free slot could be found!\n", server->num_channels, SERVER_MAX_CHANNELS);
        exit(EXIT_FAILURE);
    }

    return channel;
}


/**
 * Add a connected client to a defined channel.
 *
 * Called when a client wants to join the channel. The client must not
 * currently be in any other channel.
 *
 *      TODO FIXME
 *
 * Returns 1 (true) on success, otherwise 0.
 */
int channel_add_client(Channel *channel, Client *client)
{
    assert (channel != NULL);
    assert (client != NULL);

    if (client->channel == channel) {
        // Client is already a member of this channel, nothing to do
        return 1;
    }

    if (client->channel != NULL) {
        fprintf(stderr, "channel_add_client ERROR: client @%s is already a member of channel #%s, cannot add them to #%s. Consider calling channel_remove_client() first\n",
                client->nick, client->channel->name, channel->name);
        return 0;
    }

    // Check if this channel is already full
    if (channel->num_clients >= CHANNEL_MAX_CLIENTS) {
        fprintf(stderr, "channel_add_client ERROR: channel #%s already at its maximum client limit!\n", channel->name);
        return 0;
    }

    // Find a free slot in the client list
    int i;
    for (i = 0; i < CHANNEL_MAX_CLIENTS; i++) {
        if (channel->clients[i] != NULL) {
            continue;
        }

        // Found a free slot
        channel->clients[i] = client;
        channel->num_clients++;

        client->channel = channel;
        client->channel_clients = &channel->clients[i];

        break;
    }

    if (i == CHANNEL_MAX_CLIENTS) {
        fprintf(stderr, "channel_add_client INTERNAL ERROR: channel #%s num_clients %d < maximum %d but no free slot could be found!\n",
               channel->name, channel->num_clients, CHANNEL_MAX_CLIENTS);
        exit(EXIT_FAILURE);
    }

    // TODO FIXME
    /* Use `channel_broadcast_printf` to tell everyone else in this channel
     * that a new client has joined. The messages should look something like
     * the following:
     *
     *      pdm: is anyone here?
     *       * @astudent has joined #csc209
     *      astudent: just saying hello
     *       * @astudent left #csc209
     */

    return 1;
}


/**
 * Remove a connected client from a defined channel.
 *
 * Called when the client wants to leave. This client must currently be a
 * member of this channel, that is, they previously joined it, i.e.
 * `client->channel == channel`
 *
 *      TODO FIXME
 *
 * Returns 1 (true) on success, otherwise 0.
 */
int channel_remove_client(Channel *channel, Client *client)
{
    assert (channel != NULL);
    assert (client != NULL);

    if (client->channel != channel) {
        fprintf(stderr, "channel_remove_client ERROR: client @%s is not currently a member of channel #%s\n",
                client->nick, channel->name);
        return 0;
    }

    assert (client->channel == channel);
    assert (client->channel_clients != NULL);
    assert (client->channel_clients >= (Client **) &channel->clients);
    assert (client->channel_clients < ((Client **) &channel->clients + sizeof (channel->clients)));
    assert (channel->num_clients >= 1);
    assert (channel->server->num_channels >= 1);

    // Remove this client from the channels' client list
    client->channel = NULL;
    *client->channel_clients = NULL;
    client->channel_clients = NULL;

    channel->num_clients--;

    // Was this the last client to leave this channel? If so, the channel should go away
    if (channel->num_clients == 0) {
        // Consistency check
        int i;
        for (i = 0; i < CHANNEL_MAX_CLIENTS; i++) {
            if (channel->clients[i] != NULL) {
                fprintf(stderr, "channel_remove_client INTERNAL ERROR: channel #%s has num_clients == 0 but slot %d (@%s) is non-NULL!\n",
                        channel->name, i, channel->clients[i]->nick);
                exit(EXIT_FAILURE);
            }
        }

        assert (channel->server_channels != NULL);
        assert (channel->server_channels >= (Channel **) &channel->server->channels);
        assert (channel->server_channels < ((Channel **) &channel->server->channels + sizeof (channel->server->channels)));
        assert (channel->server->num_channels >= 1);

        // Remove the channel from the server, and release its memory
        channel->server->num_channels--;
        *channel->server_channels = NULL;
        channel->server_channels = NULL;

        free(channel->name);
        free(channel);

        return 1;
    }

    // TODO FIXME
    /* Use `channel_broadcast_printf` to tell everyone else in this channel
     * that this client has left. The messages should look something like
     * the following:
     *
     *      pdm: is anyone here?
     *       * @astudent has joined #csc209
     *      astudent: just saying hello
     *       * @astudent left #csc209
     */

    return 1;
}


/**
 * Broadcast a message to any and all clients who are currently in this channel.
 *
 *      TODO FIXME
 *
 *  Returns 1 (true) on success, otherwise 0.
 */
int channel_broadcast(Channel *channel, char *msg, int msg_len)
{
    // TODO FIXME
    /* Iterate through each of `channel->clients`, and for each non-NULL
     * pointer, use `client_write` to send `msg` to that client. */

    return 1;
}


/**
 * Use `printf` style format strings to broadcast formatted text to all clients
 * in a channel.
 *
 * See the comments for `client_printf` for more explanation of how this works.
 *
 * This function is dependent on you correctly implementing
 * `channel_broadcast`.
 *
 * Returns 1 (true) on success, otherwise 0.
 */
int channel_broadcast_printf(Channel *channel, const char *format, ...)
{
#   define BUF_SIZE     4096
    static char buf[BUF_SIZE];

    va_list vl;
    va_start(vl, format);

    int buf_len = vsnprintf(buf, sizeof (buf), format, vl);

    return channel_broadcast(channel, buf, buf_len);
}
