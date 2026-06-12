#!/usr/bin/bash

# Ask for groceries until we receive a -
# Save the groceries to a file.

db='groceries.txt'

while true; do
    echo 'Add a grocery and quantity:'
    read grocery quantity

    if [ "$grocery" = '-' ]; then
        break
    fi

    # Don't add a grocery if it already exists.
    if [ -f "$db" ] && grep -Eq "^$grocery" "$db"; then
        echo "$grocery already exists!"
    else
        echo "$grocery $quantity" >> "$db"
        echo "Added $quantity x $grocery"
        echo
    fi
done

echo "Goodbye!"
