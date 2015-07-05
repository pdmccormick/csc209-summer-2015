CC=gcc
CFLAGS=-Wall -g
LDFLAGS=
LIBS=-lreadline
DEPS=lexer.h parser.h command.h execute.h
OBJS=sh209.o lexer.o parser.o command.o execute.o

sh209: $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f sh209 $(OBJS)
