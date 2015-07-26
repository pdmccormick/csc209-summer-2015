/**
 * CSC209 Chat Server -- Client command handlers
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "command.h"
#include "client.h"
#include "channel.h"

/**
 * Handler for the `/help` command.
 *
 * Sends a summary of all of the currently recognized commands.
 *
 * Returns 1 (true) on success, otherwise 0.
 */
int command_help(Client *client)
{
    client_printf(client,
        "! Command help for the CSC209 Chat Server\n"
        "! ---------------------------------------\n"
        "!\n"
        "! Display this help message:\n"
        "!      /help\n"
        "!\n"
        "! Join a named channel:\n"
        "!      /join <channel>\n"
        "!\n"
        "! Set your nick name on this server:\n"
        "!      /nick <name>\n"
        "!\n"
        "! Disconnect from this server:\n"
        "!      /disconnect\n"
        "!\n"
        "! List all the current channels on this server:\n"
        "!      /channels\n"
        "!\n"
        "! List all the currently connected clients on this server:\n"
        "!      /who\n"
        "!\n"
        );

    return 1;
}


/**
 * Handler for the `/join` command.
 *
 *      TODO FIXME
 *
 * Returns 1 (true) on success, otherwise 0.
 */
int command_join(Client *client, char *channel_name)
{
    // TODO FIXME
    /* 1) Find the channel named `channel_name`. If it doesn't exist, create it. */

    /* 2) If the client is already in a channel, remove them from it. */

    /* 3) Add them to the new channel. */

    /* 4) Send a "/prompt" command back to the chat client with an updated
     * prompt.
     *
     * The format of the prompt should be:
     *
     *      @{nick-name} #{current-channel}
     *
     * Example: if the newly joined channel was "a4", and their nick was
     * "astudent", you should send the client the following command message:
     *
     *      /prompt @astudent #a4
     *
     * Use `client_printf` to format this message and send it to the client.
     *
     * Note: The '/nick' and '/join' commands both change the client prompt in
     * the same way, so consider using a helper function for this.
     */

    return 1;
}


/**
 * Handler for the `/nicks` command.
 *
 *      TODO FIXME
 *
 * Returns 1 (true) on success, otherwise 0.
 */
int command_nick(Client *client, char *nick)
{
    // If this is already their nick, do nothing
    if (strcmp(client->nick, nick) == 0) {
        return 1;
    }

    // Save this until the end
    char *old_nick = client->nick;

    /* Is there another client on this server who has already registered this
     * nick name? If so, respond to the client informing them that they cannot
     * use it, and return. */
    int i;
    for (i = 0; i < SERVER_MAX_CLIENTS; i++) {
        Client *other = client->server->clients[i];

        if (other != NULL &&
                other != client &&
                strcmp(other->nick, nick) == 0) {
            printf("%s (@%s): Nick @%s is already in use\n", client_addrstr(client), client->nick, nick);
            return client_printf(client, "! Nick @%s is already in use!\n", nick);
        }
    }

    // TODO FIXME
    /* 1) Set this clients' nick name.
     *
     * Remember that the `nick` argument is a pointer to someones' string
     * buffer, so make your own copy of it using `strdup`. Similarly, the
     * current value of `client->nick` was strdup'd previously, so free() that
     * old value first.
     */

    /* 2) Send a "/prompt" command back to the chat client with an updated
     * prompt.
     *
     * The format of the prompt should be:
     *
     *      @{nick-name} #{current-channel}
     *
     * Example: if the newly registered nick name was "astudent" and the
     * current channel was "csc209", you should send the client the following
     * command message:
     *
     *      /prompt @astudent #csc209
     *
     * Use `client_printf` to format this message and send it to the client.
     *
     * Note: The '/nick' and '/join' commands both change the client prompt in
     * the same way, so consider using a helper function for this.
     */

    /* 3) If the client is currently in a channel, broadcast a notice to the
     * channel, informing everyone of the nick changed. For example:
     *
     *       * @astudent has joined #csc209
     *      astudent: just saying hello
     *       * @astudent is now known as @g5stdnt
     *      g5stdnt: ta da!
     */

    // Free the previous nickname string
    free(old_nick);

    return 1;
}


/**
 * Handler for the `/disconnect` command.
 *
 *      TODO FIXME
 *
 * Returns 1 (true) on success, otherwise 0.
 */
int command_disconnect(Client *client)
{
    // TODO FIXME
    /* Before closing the client connection, use `client_printf` to send them
     * a friendly departing message. */

    client_close(client);

    return 1;
}


/**
 * Handler for the `/channels` command.
 *
 *      TODO FIXME
 *
 * Returns 1 (true) on success, otherwise 0.
 */
int command_channels(Client *client)
{
    // TODO FIXME
    /* Iterate through all the entries of `client->server->channels`
     * (from the definition, note that are a maximum of SERVER_MAX_CHANNELS
     * channels on the server): for each non-NULL entry, send the user a
     * response listing the currently joined users.
     *
     * Example:
     *
     *          !   #csc209: @g3stdnt @c4stdnt
     *          !   #a4: @pdm @testuser
     *
     * You can choose your own format for this information, but remember that
     * this is in response to a human users query, so please make it friendly
     * and readable for them.
     */

    return 1;
}


/**
 * Handler for the `/who` command.
 *
 *      TODO FIXME
 *
 * Returns 1 (true) on success, otherwise 0.
 */
int command_who(Client *client)
{
    // TODO FIXME
    /* Iterate through all the entries of `client->server->clients` (from
     * the definition, note that are a maximum of SERVER_MAX_CLIENTS clients on
     * the server): for each non-NULL entry, send the user a response listing
     * the other other clients currently connected to the server, and indicate
     * which channel they are in.
     *
     * Example:
     *
     *          !   @g3stdnt (#csc209)
     *          !   @c4stdnt (#csc209)
     *          !   @pdm (#a4)
     *          !   @testuser (#a4)
     *
     * You can choose your own format for this information, but remember that
     * this is in response to a human users query, so please make it friendly
     * and readable for them.
     */

    return 1;
}
