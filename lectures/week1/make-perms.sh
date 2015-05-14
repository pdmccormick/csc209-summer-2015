#!/bin/bash

# This script will create a directory named 'perms' containing a variety of
# files and subdirectories, and set specific permissions on them. Afterwards,
# an `ls -l` on the directory should look something like this:
#
#   -rwxr-xr-x 1 pdm instrs    0 May 14 15:16 allexec
#   -r--r--r-- 1 pdm instrs    0 May 14 15:16 allread
#   dr-xr-xr-x 2 pdm instrs 4096 May 14 15:16 dir-read
#   dr-x--x--x 2 pdm instrs 4096 May 14 15:16 dir-search
#   -rw------- 1 pdm instrs    0 May 14 15:16 ownerread
#   -r--r--r-- 1 pdm instrs    0 May 14 15:16 readonly
#

# If it exists, first delete the directory 'perms' and everything in it
# (recursively)
[ -d perms/ ] && rm -rf perms/

mkdir perms
cd perms

# Each following pair of `chmod` do the same thing, but one uses the octal
# notation and the other the symbolic user/group/other plus/minus/equal
# read/write/execute combinations

touch allexec
chmod 0755 allexec
chmod u=rwx,go=rx allexec

touch allread
chmod 0444 allread
chmod ugo=r allread

touch ownerread
chmod 0600 ownerread
chmod u=rw,go= ownerread

touch readonly
chmod 0444 readonly
chmod ugo=r readonly

mkdir dir-read
chmod 0555 dir-read
chmod ugo=rx dir-read

mkdir dir-search
chmod 0511 dir-search
chmod u=rx,go=x dir-search

