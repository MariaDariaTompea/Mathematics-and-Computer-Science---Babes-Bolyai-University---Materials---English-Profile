# Lab 02

## GCC Compiler Usage

```shell
gcc -Wall -Wextra -Werror -g -o program program.c
```

- `-Wall`: enable additional warnings.
- `-Wextra`: enable even more warnings.
- `-Werror`: treat warnings as hard errors.
- `-o program`: set the name of the executable.

## Memory Allocation

- `malloc(size)` allocates a block of memory with the given size.
- Memory allocated with `malloc` must be released with `free`.
- `malloc` and `free` are defined in the `<stdlib.h>` header.

Example:

```c
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int *numbers = malloc(3 * sizeof(int));

  numbers[0] = 1;
  numbers[1] = 2;
  numbers[2] = 3;

  free(numbers);
  return 0
}
```

## Valgrind

- `valgrind` is a tool that can be used to catch memory leaks.

Example:

```shell
valgrind ./mycat file1.txt file2.txt
```
