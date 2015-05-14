import os
import sys

# Open a file, write something to it and then close it
#
# Uses the `os` module to directly deal with integer file descriptors and the
# raw open(2), write(2) and close(2) system calls.

fd = os.open("output.txt", os.O_WRONLY | os.O_CREAT)

if fd < 0:
    # Negative return values indicate an error
    print("Cannot open output.txt for writing")
    sys.exit(-1)

count = os.write(fd, b"Hello world!")

# TODO: Unless `count == len("Hello World!")`, not all of the bytes we were
# expecting to be written necessarily have been.

os.close(fd)

