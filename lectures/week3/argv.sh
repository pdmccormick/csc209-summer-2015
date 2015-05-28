#!/bin/bash

echo "[0] = '$0'"

for K in `seq $#`; do
    echo "[$K] = '$1'"
    shift
done
