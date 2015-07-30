#!/bin/bash

echo "[0] = '$0'"

I=1
while [[ "$1" ]]; do
    echo "[$I] = \"$1\""
    I=`expr $I + 1`
    shift
done
