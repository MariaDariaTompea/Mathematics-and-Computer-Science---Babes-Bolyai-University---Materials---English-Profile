#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 256

/*
 * A simple reimplementation of the cp command.
 * Usage: ./copy source_file destination_file
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: ./copy <src> <dst>\n");
        return 1;
    }

    char *src_path = argv[1];

    // Open the file in read-only mode (O_RDONLY).
    int src_fd = open(src_path, O_RDONLY);

    // Check whether the file was opened successfully.
    if (src_fd == -1) {
        perror("Failed to open source file");
        return 2;
    }
    
    char *dst_path = argv[2];

    // Open the file in write-only mode (O_WRONLY).
    // Create the file if it doesn't exist (O_CREAT).
    // Clear any existing data in the file (O_TRUNC).
    // Set file permissions to 0644 (the leading 0 is important!).
    int dst_fd = open(dst_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // Check whether the file was opened successfully.
    if (dst_fd == -1) {
        perror("Failed to open destination file");
        return 2;
    }

    // Reserve some space for reading/writing data.
    char buf[BUF_SIZE];

    // Loop forever (or until we break from the loop).
    for (;;) {
        // Read operations return the number of bytes that could be read.
        ssize_t n = read(src_fd, buf, BUF_SIZE);

        // Read operations return zero when we reach the end of the file.
        if (n == 0) {
            break;
        }

        // Ideally, we should check the return value of read/write operations,
        // but to keep thing simple we will assume that they always succeed.
        write(dst_fd, buf, n);
    }
    
    // Close the file descriptors after we are done working with them.
    close(src_fd);
    close(dst_fd);

    return 0;
}
