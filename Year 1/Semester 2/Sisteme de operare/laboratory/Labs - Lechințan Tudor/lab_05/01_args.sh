#!/usr/bin/bash

# " - Variable interpolation is enabled.
echo "Executable name: $0"

# ' - Variable interpolation is enabled.
echo 'Executable name: $0'

# # - Number of arguments without executable name.
echo "Argument count: $#"

# Iterate over all arguments.
for arg in "$@"; do
    echo " -> $arg"
done

# Access argument by index.
echo "First argument: $1"

# $? - Return value of last command.

# 0 - Success.
test 123 -lt 456
echo "$?"

# 1 - Failure.
test 123 -gt 456
echo "$?"

# Test can compare numbers (and more).
if test "$1" -lt "$2"; then
    echo "$1 < $2"
elif test "$1" -gt "$2"; then
    echo "$1 > $2"
else
    echo "$1 = $2"
fi

# [ ... ] can compare numbers (and more).
if [ "$1" -lt "$2" ]; then
    echo "$1 < $2"
elif [ "$1" -gt "$2" ]; then
    echo "$1 > $2"
else
    echo "$1 = $2"
fi

