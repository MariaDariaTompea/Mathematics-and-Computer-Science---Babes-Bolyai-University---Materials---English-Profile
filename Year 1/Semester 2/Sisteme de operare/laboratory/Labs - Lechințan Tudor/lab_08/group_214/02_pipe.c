#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	// Parent to child.
	// 0: read
	// 1: write
	int pc_pipe[2] = {0};

	if (pipe(pc_pipe) == -1) {
		perror("pipe");
		return 1;
	}

	// Child to parent.
	// 0: read
	// 1: write
	int cp_pipe[2] = {0};

	if (pipe(cp_pipe) == -1) {
		perror("pipe");
		return 1;
	}

	int pid = fork();

	if (pid == -1) {
		perror("fork");
	}

	if (pid == 0) {
		// Close the fds we don't need.
		close(pc_pipe[1]);
		close(cp_pipe[0]);

		for (;;) {
			// Child reads from parent.
			char buf[6];
			read(pc_pipe[0], buf, 6);
			write(1, buf, 6);

			// Child writes to parent.
			write(cp_pipe[1], "Hello from child\n", 18);
		}

		close(pc_pipe[0]);
		close(cp_pipe[1]);
	} else {
		// Close the fds we don't need.
		close(pc_pipe[0]);
		close(cp_pipe[1]);

		for (;;) {
			// Parent writes to child.
			write(pc_pipe[1], "Hello\n", 6);

			// Parent read from child.
			char buf[18];
			read(cp_pipe[0], buf, 18);
			write(1, buf, 18);
		}

		close(pc_pipe[1]);
		close(cp_pipe[0]);
	}
	
	return 0;
}
