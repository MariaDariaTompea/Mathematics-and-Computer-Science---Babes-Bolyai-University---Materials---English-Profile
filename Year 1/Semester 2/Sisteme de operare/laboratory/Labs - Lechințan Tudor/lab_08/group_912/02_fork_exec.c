#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	printf("Parent: Start\n");

	int pid = fork();

	if (pid == -1) {
		perror("fork");
		return 1;
	}

	if (pid == 0) {
		// Child
		printf("Child: Start with pid %d\n", getpid());

		char *const ls_args[] = { "ls", "-l", NULL };

		if (execvp("ls", ls_args) == -1) {
			perror("execvp");
			return 1;
		}

		printf("Child: Exit\n");
	} else {
		// Parent
		printf("Parent: Child has pid %d\n", pid);

		if (wait(NULL) == -1) {
			perror("wait");
			return 1;
		}

		printf("Parent: Exit\n");
	}

	return 0;
}
