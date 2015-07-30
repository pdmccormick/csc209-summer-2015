#!/bin/bash

if [[ $# -eq 0 ]]; then
    echo "usage: $0 status"
    exit -1
fi

exit $1
