#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	printf("Parent: Start\n");

	int pid = fork();

	if (pid == -1) {
		perror("fork");
		return 1;
	}

	if (pid == 0) {
		// Pid is 0 in child process.
		printf("Child: Start with pid %d\n", getpid());

		char *const ls_args[] = { "ls", "-l", NULL };

		// Replace the code of the current process
		// with the code of the ls program.
		if (execvp("ls", ls_args) == -1)  {
			perror("excvp");
			return 2;
		}

		// Won't be executed!
		printf("Child: Exit\n");
	} else {
		// Pid is the pid of the child in the parent process.
		printf("Parent: Child pid is %d\n", pid);
		printf("Parent: Waiting for child to finish...\n");

		if (wait(NULL) == -1) {
			perror("wait");
			return 2;
		}

		// Parent process.
		printf("Parent: Exit\n");
	}

	return 0;
}
