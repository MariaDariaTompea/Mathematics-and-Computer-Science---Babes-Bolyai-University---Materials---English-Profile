#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *run_thread_a(void *arg) {
    printf("Started thread A\n");
    sleep(2);
    printf("Finished thread A\n");

    int *return_value = malloc(sizeof(int));
    *return_value = 67;
    return return_value;
}

int main(int argc, char *argv[]) {
    printf("Started main thread\n");

    pthread_t thread_a = {0};
    pthread_create(
        &thread_a,
        NULL,
        run_thread_a,
        NULL
    );

    printf("Waiting for thread A...\n");

    int *return_value = NULL;
    pthread_join(thread_a, (void**)&return_value);
    printf("Thread A returned %d\n", *return_value);
    free(return_value);

    printf("Finished main thread\n");
    return 0;
}
