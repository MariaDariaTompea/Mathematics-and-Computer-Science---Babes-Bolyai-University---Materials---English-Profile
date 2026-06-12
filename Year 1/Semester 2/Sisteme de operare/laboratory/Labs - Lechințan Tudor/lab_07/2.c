#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void spawn_process(int idx) {
	int pid = fork();

	if (pid == -1) {
		perror("Failed to fork");
		return;
	}

	// We are the parent.
	if (pid != 0) {
		return;	
	}

	// We are the child.
	int sum = 0;
	for (int i = 1; i <= idx; ++i) {
		sum += i;
	}

	printf("Child %d: sum is %d\n", getpid(), sum);

	/*
		Always call exit in the child process
		after finishing work, otherwise it will
		start executing code that was intended for
		the parent.
	*/
	exit(0);
}

/*
	Spawn a number of child processes.

	./2 <child-process-count>
*/
int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: ./2 <child-process-count>\n");
		return 1;
	}

	int count = 0;
	sscanf(argv[1], "%d", &count);	
	
	printf("Parent: spawning %d children\n", count);
	for (int i = 0; i < count; ++i) {
		spawn_process(i);		
	}

	for (int i = 0; i < count; ++i)	{
		int child_pid = wait(NULL);

		if (child_pid == -1) {
			perror("Failed to wait");
			continue;
		}

		printf("Parent: child %d exited\n", child_pid);
	}
}
