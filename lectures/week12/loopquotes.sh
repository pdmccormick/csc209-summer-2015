#!/bin/bash

for ARG in "$*"; do
    echo '"$*"' "$ARG"
done
echo

for ARG in $*; do
    echo '$*' "$ARG"
done
echo

for ARG in "$@"; do
    echo '"$@"' "$ARG"
done
echo

for ARG in $@; do
    echo '$@' "$ARG"
done
