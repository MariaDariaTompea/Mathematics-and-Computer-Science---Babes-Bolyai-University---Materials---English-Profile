#!/usr/bin/bash

# Input:
# - list of files and folders
#
# For each entry:
# - if file:
#   display all lines that contain numbers
#
# - if folder:
#   display the name of the largest file in the directory

for arg in "$@"; do
    if [ -f "$arg" ]; then
        grep -E '[0-9]' "$arg"
    elif [ -d "$arg" ]; then
        # sort -nr: sort numberically in reverse.
        # head -n 1: only output the first line.
        # cut -f 2: only output the second field.
        du -b "$arg"* \
            | sort -nr \
            | head -n 1 \
            | cut -f 2
    else
        echo "'$arg' is not a file or directory!"
        exit 1
    fi
done
