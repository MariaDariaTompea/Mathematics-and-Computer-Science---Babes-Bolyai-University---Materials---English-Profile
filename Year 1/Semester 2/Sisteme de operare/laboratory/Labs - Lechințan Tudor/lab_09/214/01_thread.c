#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *thread_a_run(void *arg) {
    printf("Started thread A\n");
    sleep(1);
    printf("Running thread A\n");
    sleep(1);
    printf("Stopped thread A\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    printf("Started main thread\n");

    pthread_t thread_a = {0};
    if (pthread_create(
        &thread_a,
        NULL,
        thread_a_run,
        NULL
    ) != 0) {
        printf("Failed to create thread A\n");
        return 1;
    }

    sleep(1);
    printf("Running main thread\n");
    sleep(1);

    pthread_join(thread_a, NULL);

    printf("Stopped main thread\n");
    return 0;
}
