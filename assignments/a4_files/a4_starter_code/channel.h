/**
 * CSC209 Chat Server -- Channel management
 */
#ifndef __CHANNEL_H
#define __CHANNEL_H

#include "defs.h"

Channel *channel_new(Server *server, char *name);
Channel *channel_find(Server *server, char *name);
int channel_add_client(Channel *channel, Client *client);
int channel_remove_client(Channel *channel, Client *client);
int channel_broadcast(Channel *channel, char *msg, int msg_len);
int channel_broadcast_printf(Channel *channel, const char *format, ...);

#endif /* __CHANNEL_H */
