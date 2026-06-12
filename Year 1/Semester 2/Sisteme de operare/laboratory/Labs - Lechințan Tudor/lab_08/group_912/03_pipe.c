#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 100

int main(int argc, char *argv[]) {
	// Parent to child pipe.
	int pc_pipe[2];

	if (pipe(pc_pipe) == -1) {
		perror("pipe");
		return 1;
	}

	// Child to parent pipe.
	int cp_pipe[2];

	if (pipe(cp_pipe) == -1) {
		perror("pipe");
		return 1;
	}

	int pid = fork();

	if (pid == -1) {
		perror("fork");
		return 1;
	}

	if (pid == 0) {
		close(pc_pipe[1]);
		close(cp_pipe[0]);

		for (;;) {
			// Read data from parent.
			char buf[BUF_SIZE];
			size_t buf_size = read(pc_pipe[0], buf, BUF_SIZE);
			write(1, buf, buf_size);

			// Send data to parent.
			const char *message = "Sent by child, displayed by parent\n";
			size_t message_len = strlen(message);
			write(cp_pipe[1], message, message_len);
		}

		close(pc_pipe[0]);
		close(cp_pipe[1]);
	} else {
		close(pc_pipe[0]);
		close(cp_pipe[1]);

		for (;;) {
			// Send data to child.
			const char *message = "Sent by parent, displayed by child\n";
			size_t message_len = strlen(message);
			write(pc_pipe[1], message, message_len);

			// Read data from child.
			char buf[BUF_SIZE];
			size_t buf_size = read(cp_pipe[0], buf, BUF_SIZE);
			write(1, buf, buf_size);

			sleep(2);
		}

		close(pc_pipe[1]);
		close(cp_pipe[0]);
	}

	return 0;
}
