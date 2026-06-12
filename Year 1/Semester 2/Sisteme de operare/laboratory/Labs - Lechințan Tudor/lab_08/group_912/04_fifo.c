#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 100

int read_fifo(void) {
	printf("Started read_fifo...\n");
	int fd = open("fifo.pipe", O_RDONLY);

	if (fd == -1) {
		perror("open");
		return 1;
	}

	char buf[BUF_SIZE];
	size_t buf_size = read(fd, buf, BUF_SIZE);
	write(1, buf, buf_size);

	close(fd);

	printf("Finished read_fifo...\n");
	return 0;
}

int write_fifo(void) {
	printf("Started write_fifo...\n");
	int fd = open("fifo.pipe", O_WRONLY);

	if (fd == -1) {
		perror("open");
		return 1;
	}

	const char *message = "Hello\n";
	size_t message_len = strlen(message);
	write(fd, message, message_len);

	close(fd);

	printf("Finished write_fifo...\n");
	return 0;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: ./04_fifo <mode>\n");
		return 1;
	}

	if (strcmp(argv[1], "read") == 0) {
		return read_fifo();
	} else if (strcmp(argv[1], "write") == 0) {
		return write_fifo();
	} else {
		printf("Usage: ./04_fifo <mode>\n");
		return 1;
	}
}
