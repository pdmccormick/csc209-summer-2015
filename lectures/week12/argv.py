#!/usr/bin/env python3

import sys

if __name__ == '__main__':
    for i, arg in enumerate(sys.argv):
        print("[%d] = '%s'" % (i, arg))
