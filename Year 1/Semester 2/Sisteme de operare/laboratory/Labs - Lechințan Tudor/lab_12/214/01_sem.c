#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_ITERATIONS 3

void *run_thread(void *arg) {
    int id = *(int*)arg;

    for (int i = 1; i <= NUM_ITERATIONS; ++i) {
        printf("Iteration %d, thread %d\n", i, id);

        // Simulate heavy work.
        sleep(1);
    }

    free(arg);
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: ./01_sem <num-threads> <sem-capacity>\n");
        return 1;
    }

    int num_threads = 0;
    sscanf(argv[1], "%d", &num_threads);

    int sem_capacity = 0;
    sscanf(argv[2], "%d", &sem_capacity);

    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));

    for (int i = 0; i < num_threads; ++i) {
        int *id = malloc(sizeof(int));
        *id = i;

        pthread_create(
            &threads[i],
            NULL,
            run_thread,
            id
        );
    }

    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    return 0;
}
