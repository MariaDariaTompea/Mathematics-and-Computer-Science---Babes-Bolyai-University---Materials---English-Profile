#!/usr/bin/bash

# Add users to a database.

db='users.txt'

if [ "$#" -ne 1 ]; then
    echo 'Usage: ./user.sh add'
    exit 1
fi

if [ "$1" = 'add' ]; then
    while true; do
        echo "Input user and group:"
        read new_user new_group

        if [ -n "$new_user" ] && [ -n "$new_group" ]; then
            break
        fi
    done

    echo "$new_user $new_group" >> "$db"

    # Remove duplicates...
    sort "$db" | uniq > "$db.temp"
    mv "$db.temp" "$db"
else
    echo "Unknown command '$1'"
    exit 1
fi
