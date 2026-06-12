#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_a_run(void *arg) {
    printf("Started thread A\n");
    sleep(1);
    printf("Running thread A\n");
    sleep(1);
    printf("Stopped thread A\n");

    int *return_value = malloc(sizeof(int));
    *return_value = 67;
    return return_value;
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

    int *thread_return_value = NULL;
    pthread_join(thread_a, (void**)&thread_return_value);
    printf("Thread returned %d\n", *thread_return_value);
    free(thread_return_value);

    printf("Stopped main thread\n");
    return 0;
}
