#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t mutex;

void *run_thread(void *arg) {
    for (int i = 0; i < 1000000; ++i) {
        // Blocks if mutex is locked.
        pthread_mutex_lock(&mutex);

        counter += 1;
        
        // Unlocks the mutex.
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_mutex_init(&mutex, NULL);

    pthread_t thread_a = {0};
    pthread_create(
        &thread_a,
        NULL,
        run_thread,
        NULL
    );

    for (int i = 0; i < 1000000; ++i) {
        // Blocks if mutex is locked.
        pthread_mutex_lock(&mutex);

        counter += 1;
        
        // Unlocks the mutex.
        pthread_mutex_unlock(&mutex);
    }

    pthread_join(thread_a, NULL);
    pthread_mutex_destroy(&mutex);

    printf("Counter: %d\n", counter);
    return 0;
}
