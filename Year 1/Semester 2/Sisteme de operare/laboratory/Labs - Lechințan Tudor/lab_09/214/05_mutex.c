#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int counter = 0;
pthread_mutex_t mutex;

void *thread_a_run(void *arg) {
    for (int i = 0; i < 1000000; ++i) {
        // Blocks if lock is taken.
        pthread_mutex_lock(&mutex);

        counter += 1;
        
        // Release the lock.
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_mutex_init(&mutex, NULL);

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

    for (int i = 0; i < 1000000; ++i) {
        // Blocks if lock is taken.
        pthread_mutex_lock(&mutex);

        counter += 1;

        // Release the lock.
        pthread_mutex_unlock(&mutex);
    }

    pthread_join(thread_a, NULL);
    pthread_mutex_destroy(&mutex);

    printf("Counter: %d\n", counter);
    return 0;
}
