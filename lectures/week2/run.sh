#!/bin/bash

INFILE=$1

gcc -Wall -g $INFILE -o program
./program
