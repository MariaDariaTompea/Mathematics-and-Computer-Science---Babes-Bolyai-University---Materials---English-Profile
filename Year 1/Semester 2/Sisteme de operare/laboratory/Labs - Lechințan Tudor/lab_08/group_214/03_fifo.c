#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 100

int read_fifo(void) {
	printf("Waiting for writer...\n");
	int fd = open("fifo.pipe", O_RDONLY);

	if (fd == -1) {
		perror("open");
		return 1;
	}

	printf("Started reading...\n");

	char buffer[BUFFER_SIZE + 1];
	size_t n = read(fd, buffer, BUFFER_SIZE);

	buffer[n] = '\0';
	printf("Received from fifo: %s\n", buffer);

	printf("Finished reading...\n");
	close(fd);

	return 0;
}

int write_fifo(void) {
	printf("Waiting for reader...\n");
	int fd = open("fifo.pipe", O_WRONLY);

	if (fd == -1) {
		perror("open");
		return 1;
	}

	printf("Started writing...\n");


	const char *message = "Hello";
	size_t message_len = strlen(message);
	write(fd, message, message_len);

	printf("Finished writing\n");
	close(fd);

	return 0;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: ./03_fifo <mode>\n");
		return 1;
	}

	if (strcmp(argv[1], "read") == 0) {
		return read_fifo();
	} else {
		return write_fifo();
	}
}
