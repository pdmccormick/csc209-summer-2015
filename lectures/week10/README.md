CSC209 Summer 2015 - Week 10
============================

Thursday, July 16, 2015

Suggested Exercises
-------------------

 - `chatclient.c`: modify `simpleget.c` (removing the HTTP specific bits) so that it reads keystrokes from standard input and sends them to the connected server (test against your own `nc -vlk localhost $PORT` server)
 - `echoserver.c`: modify `acceptclose.c` so that, instead of closing the client socket immediately, it instead reads from that socket and writes those exact same bytes (echoing) back to the client (use your `chatclient.c`, or `nc -v localhost $PORT` as your connecting client)
    * Run your echoserver, and run two instances of the client: what do you notice about the second client?
    * What happens to the second client once you disconnect the first? (hit CTRL-C to send the SIGINT interruption signal, or CTRL-D to indicate EOF on the standard input)
    * Why is this happening?
 - `forkechoserver.c`: modify your `echoserver.c` so that, once it accepts the client connection, the process forks a child process to actually perform the echoing
    * How does this server handle two simultaneous clients?
    * Remember what was required when forking with an open pair of pipe file descriptors, one of which you were not going to use, and consider how that might come into play here

**Question:** Did you notice how a simple two-way `nc` chatserver (`nc -vlk localhost $PORT` for the server, and `nc -v localhost $PORT` for the client) can both accept standard input to send through the socket, and print out whatever it received from the socket? Could you create a server or client to do this?
