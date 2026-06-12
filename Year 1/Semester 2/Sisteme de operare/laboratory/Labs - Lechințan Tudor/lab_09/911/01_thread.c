#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *run_thread_a(void *arg) {
    sleep(1);
    printf("Started thread A\n");
    sleep(2);
    printf("Finished thread A\n");
    return NULL;
}

void *run_thread_b(void *arg) {
    sleep(1);
    printf("Started thread B\n");
    sleep(2);
    printf("Finished thread B\n");
    return NULL;
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

    pthread_t thread_b = {0};
    pthread_create(
        &thread_b,
        NULL,
        run_thread_b,
        NULL
    );

    sleep(1);

    printf("Waiting for thread A...\n");
    pthread_join(thread_a, NULL);

    printf("Waiting for thread B...\n");
    pthread_join(thread_b, NULL);

    printf("Finished main thread\n");
    return 0;
}
