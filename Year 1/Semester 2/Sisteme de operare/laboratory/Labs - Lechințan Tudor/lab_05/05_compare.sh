#!/usr/bin/bash

# Our program requires 3 arguments
# num1 </>/= num2
#
# num1 is equal than num2

# num1 is not equal to num2
# num1 is less to num2
# num1 is not less than num2
# num1 is greater than num2
# num1 is not greater than num2
#
# ./compare 100 < 40
# 100 is not less than 40

# ./compare 40 = 40
# 40 is equal to 40

if [ "$#" -ne 3 ]; then
    echo 'Wrong argument count'
    exit 1
fi

if [ "$2" = '<' ]; then
    if [ "$1" -lt "$3" ]; then
        echo "$1 is less than $3"
    else
        echo "$1 is not less than $3"
    fi
elif [ "$2" = '>' ]; then
    if [ "$1" -gt "$3" ]; then
        echo "$1 is greater than $3"
    else
        echo "$1 is not greater than $3"
    fi
elif [ "$2" = '=' ]; then
    if [ "$1" -eq "$3" ]; then
        echo "$1 is equal to $3"
    else
        echo "$1 is not equal to $3"
    fi
else
    echo "Unknown operation '$2'"
    exit 1
fi
