#!/usr/bin/env python3

import sys

if __name__ == '__main__':
    exit_code = 0

    if len(sys.argv) > 1:
        exit_code = int(sys.argv[1])

    sys.exit(exit_code)

