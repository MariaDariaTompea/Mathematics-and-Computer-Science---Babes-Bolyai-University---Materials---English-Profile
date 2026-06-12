#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 100

int main(int argc, char *argv[]) {
	// Pipes are unidirectional.
	// Parent to child.
	int pc_pipe[2];

	if (pipe(pc_pipe) == -1) {
		perror("pipe");
		return 1;
	}

	// Child to parent.
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
		// Child

		// Close the write end.
		close(pc_pipe[1]);
		close(cp_pipe[0]);

		for (;;) {
			// Child reads from parent.
			char buf[BUF_SIZE];
			size_t buf_size = read(pc_pipe[0], buf, BUF_SIZE);
			write(1, buf, buf_size);

			// Child writes to parent.
			const char *message = "Sent by child, written by parent\n";
			size_t message_len = strlen(message);
			write(cp_pipe[1], message, message_len);
		}

		// Close the read end.
		close(pc_pipe[0]);
		close(cp_pipe[1]);
	} else {
		// Parent
		
		// Close the read end.
		close(pc_pipe[0]);
		close(cp_pipe[1]);

		for (;;) {
			// Parent writes to child.
			const char *message = "Sent by parent, written by child\n";
			size_t message_len = strlen(message);
			write(pc_pipe[1], message, message_len);

			// Parent reads from child.
			char buf[BUF_SIZE];
			size_t buf_size = read(cp_pipe[0], buf, BUF_SIZE);
			write(1, buf, buf_size);

			sleep(2);
		}

		// Close the write end.
		close(pc_pipe[1]);
		close(pc_pipe[0]);
	}

	return 0;
}
