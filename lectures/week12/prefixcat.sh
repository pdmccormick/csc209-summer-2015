#!/bin/bash

INFILE=$1

while read LINE; do
    echo "$INFILE: $LINE"
done < "$INFILE"
