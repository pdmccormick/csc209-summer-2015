/**
 * CSC209 Chat Server -- Client command handlers
 */
#ifndef __COMMAND_H
#define __COMMAND_H

#include "defs.h"

int command_help(Client *client);
int command_join(Client *client, char *channel_name);
int command_nick(Client *client, char *name);
int command_disconnect(Client *client);
int command_channels(Client *client);
int command_who(Client *client);

#endif /* __DEFS_H */
