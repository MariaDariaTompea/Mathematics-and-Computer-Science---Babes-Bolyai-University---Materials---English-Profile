# Lab 01

## Shell Commands

### Files

- `pwd`: print working directory
- `ls`: list files in a directory
- `cd`: change working directory
- `touch`: create files
- `mkdir`: created directories
- `rm`: remove files
- `cat`: concatenate files

### Misc

- `echo`: echoes back the provided text
- `man`: opens the manual page for a given program

### Redirects

Output data that is usually printed to the screen can be redirected to a file.
The sequence below creates a file named "hello.txt" wich contains "Hello,
world!".

```shell
echo 'Hello, world!' > hello.txt
```

### Pipes

The output of one program can be used as an input to another program. The
sequence below displays a list of names sorted alphabetically.

```shell
cat names.txt | sort
```

## VIM

Vim is a modal text editor, which means that keypresses don't always result in
text being inserted in the file.

### Normal Mode

Can be reached from any other mode by pressing the `ESC` key.

- `h`: move cursor left.
- `j`: move cursor down.
- `k`: move cursor up.
- `l`: move cursor right.

### Switching to Insert Mode

Insert mode can be reached from normal mode with several commands:

- `i`: insert to the left of the cursor.
- `a`: append to the right of the cursor.
- `I`: insert at the begining of the line.
- `A`: append at the end of the line.
- `o`: insert a newline below the current row.
- `O`: insert a newline above the current row.

### Command Mode:

Can be reached from normal mode by using `:` (`shift+;`)

- `w`: saves the file.
- `w file.txt` saves the file with a custom name.
- `q`: quits the program.
- `wq`: saves the file and quits the program.

## C Programming

C source files can be compiled with `gcc` using the following command:

```shell
gcc -Wall -Wextra -g -o program program.c
```
