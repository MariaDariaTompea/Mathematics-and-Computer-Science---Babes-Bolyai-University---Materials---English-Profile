# Lab 03

## IO Syscalls

The `fopen`, `fread` and `fwrite` functions are high-level functions available
on all platforms. Internally, they use lower-level functions exposed by the
specific platform our program is running on. On Linux and other Unix-like
platforms, these lower-level functions are:

- `open(path, flags, permissions)`: open a file for reading/writing
- `read(fd, buf, buf_size)`: read up to `buf_size` bytes into a buffer
- `write(fd, buf, buf_size)`: write up to `buf_size` bytes into a file

These functions use special CPU instructions to call functions implemented in
the kernel (syscalls). IO syscalls may fail, e.g. when trying to open a file
that doesn't exist. When that happens, these functions return `-1` and set the
`errno` global variable to the appropriate error code. When that happens, we can
use `perror` to display a user-friendly error message describing what happened.

Syscalls are documented in section #2 of the manual. To access the documentation
for a specific syscall, use `man 2 <syscall>`, e.g. `man 2 open`.
