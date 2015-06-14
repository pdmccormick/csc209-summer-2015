CC=gcc
CFLAGS=-Wall -g
LDFLAGS=

OBJS=heap209.o diagnostics.o

all: test-basic1

test-basic1: test-basic1.o $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c heap209.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f test-basic1 *.o
