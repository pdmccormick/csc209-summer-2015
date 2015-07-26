/**
 * CSC209 Chat Server -- Core data structure definitions
 */
#ifndef __DEFS_H
#define __DEFS_H

#include <sys/select.h>
#include <netinet/in.h>

#define SERVER_MAX_CLIENTS          (FD_SETSIZE)
#define SERVER_MAX_CHANNELS         256

#define CHANNEL_MAX_CLIENTS         SERVER_MAX_CLIENTS

typedef struct _server Server;
typedef struct _client Client;
typedef struct _channel Channel;

struct _server {
    /** The listening socket file descriptor for this server */
    int sockfd;

    /** The bind() address of this server */
    struct sockaddr_in addr;

    /** Number of currently connected clients */
    int num_clients;

    /** A set of all currently active socket file descriptors (both clients and
     * the listening server socket) */
    fd_set all_sock_fds;

    /** The largest file descriptor in the `all_sock_fds` set */
    int max_fd;

    /** All currently connected clients (a NULL pointer indicates no client
     * connection is stored in that slot) */
    Client *clients[SERVER_MAX_CLIENTS];

    /** Number of channels currently active on this server */
    int num_channels;

    /** The currently active channels on this server */
    Channel *channels[SERVER_MAX_CHANNELS];
};

struct _client {
    /** The server that this client is currently connected to */
    Server *server;

    /** Socket file descriptor for this client */
    int sockfd;

    /** Client address returned by accept() system call */
    struct sockaddr_in addr;

    /** Nickname of this client */
    char *nick;

    /** Pointer to the `Server.clients` entry that points to this client */
    Client **server_clients;

    /** Current channel of this client */
    Channel *channel;

    /** Pointer to the `Channel.clients` entry that points to this client */
    Client **channel_clients;
};

struct _channel {
    /** The server that this channel is currently registered on */
    Server *server;

    /** Name of this channel */
    char *name;

    /** Pointer to the `Server.channels` entry that points to this channel */
    Channel **server_channels;

    /** Number of currently connected clients */
    int num_clients;

    /** All clients who are currently members of this channel */
    Client *clients[CHANNEL_MAX_CLIENTS];
};

#endif /* __DEFS_H */
