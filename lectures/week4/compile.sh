#!/bin/bash

INFILE=$1
BINDIR="./bin"
OUTFILE="${BINDIR}/${INFILE%.c}"

# If the BINDIR does not exist, create it now
[[ ! -d "${BINDIR}/" ]] && mkdir "${BINDIR}/"

# Compile the source
gcc -g -Wall "${INFILE}" -o "${OUTFILE}"

echo "${OUTFILE}"
