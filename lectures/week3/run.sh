#!/bin/bash

INFILE=$1
BINDIR="./bin"
OUTFILE="${BINDIR}/${INFILE%.c}"

# Throw away the shell scripts' argv[0]
shift

# If the BINDIR does not exist, create it now
[[ ! -d "${BINDIR}/" ]] && mkdir "${BINDIR}/"

# Compile the source and only execute it if GCC does not report an error
gcc -g -Wall "${INFILE}" -o "${OUTFILE}" && exec "${OUTFILE}" $*
