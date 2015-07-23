CSC209 Summer 2015 - Week 11
============================

Thursday, July 23, 2015

Suggested Exercises
-------------------

 - `stdinserver.c`: Modify `multiserver.c` to add the standard input file descriptor to the read set, and whenever you read input from it, send that received data to all currently connected clients
 - `chatserver.c`: Further modify `multiserver.c` (or your `stdinserver.c`) so that whenever a connected client sends data to the server it is re-broadcasted to all the other currently connected clients
 - (Hard) `bigwriteserver.c`:
    * Modify `chatserver.c` by restructuring the code so that instead of making immediate write()'s to connected client descriptors (in order to send them things) you instead add that to-be-written data into a per-client pending write buffer
    * When the write buffer is non-empty for a given client, ensure that the client descriptor is in the _write_ set to the select() call
    * Check the write set after the select() for each client with a non-empty write buffer, and if it is ready for writing, drain the current contents of the buffer with a write() call
    * Test your code by piping a large text file to one netcat client, while capturing the output of another and compare for equality using `diff`. Example: in one shell, run `/bin/nc localhost $PORT > capture.txt` and then in another run `cat huge.txt | /bin/nc localhost $PORT`. Now run `diff -u huge.txt capture.txt`. Do these files only differ in the extra output lines produced by your server, and not the specific contents that the one client transmitted through the server to the other receiving client?
    * Experiment with different sized per-client pending write buffers and different sized text files. Does any part of the data ever get lost?
    * What happens if your pending write buffer becomes full?
