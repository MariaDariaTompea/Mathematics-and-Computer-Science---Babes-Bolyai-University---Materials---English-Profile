#!/usr/bin/bash

# Read folders from the keyboard until - is typed
# For each read folder display the number of files
# that have more that 100 bytes (use find for that ;)).

while true; do
    echo 'Input a directory:'
    read entry

    if [ "$entry" = '-' ]; then
        echo 'Goodbye!'
        break
    fi

    # `...` is used to store the output of a pipeline.
    echo `find "$entry" -type f -size +100c | wc -l`
done
