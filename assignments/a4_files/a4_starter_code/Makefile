CC=gcc
CFLAGS=-Wall -g
LDFLAGS=
LIBS_SERVER=
LIBS_CLIENT=-lreadline
DEPS=defs.h util.h client.h channel.h
OBJS_SERVER=util.o channel.o client.o command.o util.o chatserver.o
OBJS_CLIENT=util.o chatclient.o

all: chatclient chatserver

chatserver: $(OBJS_SERVER)
	$(CC) $(LDFLAGS) $^ $(LIBS_SERVER) -o $@

chatclient: $(OBJS_CLIENT)
	$(CC) $(LDFLAGS) $^ $(LIBS_CLIENT) -o $@

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f chatserver chatclient $(OBJS_SERVER) $(OBJS_CLIENT)
