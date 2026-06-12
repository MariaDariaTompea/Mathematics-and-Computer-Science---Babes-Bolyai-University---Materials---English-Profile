#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Volatile makes sure that the compiler picks up the changes
// that happen to the variable in signal handlers.
volatile int signal_happened = 0;

// Signal handlers get called when the signal they are registered
// to occurs.
void signal_handler(int signum) {
	signal_happened = 1;
}

int main(int argc, char *argv[]) {
	// Set the signal handler for the SIGINT signal (ctrl+c).
	signal(SIGINT, signal_handler);

	for (;;) {
		if (signal_happened) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}

		sleep(3);
	}

	return 0;
}
