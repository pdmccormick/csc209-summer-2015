CSC209 Summer 2015 - Week 9
===========================

Thursday, July 9, 2015

Suggested Exercises
-------------------

Starting from `pipeforkcat.c`, modify (or rewrite) the code to do the following:

 - `siblingcat.c`: create a pair of descriptors using `pipe()`, and then fork two child processes:
    * Child A reads the file contents and writes them into the pipe
    * Child B reads from the pipe and writes it to *stdout*
    * Parent process waits for both children to terminate
 - `twowaycat.c`: create *two* pipes, and fork one child process
    * Setup pipe #1 to communicate from the parent to the child
    * Setup pipe #2 to communicate from the child to the parent
    * The parent reads file data and writes it to the child through pipe #1
    * The child reads from pipe #1 and writes it back out to pipe #2
    * The parent reads from pipe #2 and outputs it to *stdout*
    * **HINT:** If you *don't* interleave the parent writing to pipe #1 and reading from pipe #2, you may notice that your program will appear to hang when you try it with a large-ish file (> 64 KB), because on Linux the default in-kernel buffer size for pipes is 64 KB, so some of your reads and write system calls may be blocking...

Once completed, try writing these two programs again from scratch, *without* using `pipeforkcat.c` as as starting point.
