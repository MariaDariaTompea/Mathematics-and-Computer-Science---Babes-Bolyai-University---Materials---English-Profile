#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

// All variables modified in signal handlers
// must be volatile!
volatile int should_exit = 0;

void handle_signal(int code) {
	const char *message = "\nSIGNAL!\n";
	size_t message_len = strlen(message);
	write(1, message, message_len); 

	should_exit = 1;
}

int main(int argc, char *argv[]) {
	signal(SIGINT, handle_signal);

	while (!should_exit) {
		printf("Running %d\n", getpid());
		sleep(1);
	}

	return 0;
}
