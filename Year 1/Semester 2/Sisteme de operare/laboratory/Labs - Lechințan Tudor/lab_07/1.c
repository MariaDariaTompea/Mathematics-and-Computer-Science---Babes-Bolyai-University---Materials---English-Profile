#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	/*
		The arguments array must be NULL terminated.
		The first argument must be the name of the
		program.
	*/
	char *const args[] = {
		"cat", "1.c", NULL,
	};

	/*
		execvpe searches the PATH
		envirnoment variable for
		executables to run.
	*/
	if (execvp("cat", args) == -1) {
		/*
			perror pretty-prints errors
			stored in the errno global
			variable.
		*/
		perror("Failed to exec");
		return 1;
	}

	return 0;
}
