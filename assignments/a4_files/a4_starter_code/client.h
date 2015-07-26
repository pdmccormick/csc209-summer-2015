/**
 * CSC209 Chat Server -- Client connection management
 */
#ifndef __CLIENT_H
#define __CLIENT_H

#include "defs.h"

Client *client_new(Server *server);
int client_write(Client *client, const void *buf, size_t nbyte);
int client_printf(Client *client, const char *format, ...);
void client_close(Client *client);
const char *client_addrstr(Client *client);

#endif /* __CLIENT_H */
