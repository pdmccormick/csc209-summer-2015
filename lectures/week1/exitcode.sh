#!/bin/bash

# Does the same thing as exitcode.py

if [[ $# -eq 0 ]]; then
    exit 0
fi

exit $1

