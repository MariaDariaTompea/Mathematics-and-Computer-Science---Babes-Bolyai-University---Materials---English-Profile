#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_ROUNDS 3
#define NUM_THREADS 3

// Barriers have an internal couter that tracks how many threads are currently
// waiting. The purpose of barriers is to synchornize the execution of multiple
// threads.
pthread_barrier_t barrier;

void *run_thread(void *arg) {
    int id = *(int*)arg;
    
    for (int round = 1; round <= NUM_ROUNDS; ++round) {
        // Increments the barrier's internal counter.
        //
        // Blocks if the new counter value is less that ther barrier capacity.
        //
        // If the new counter is equal to the barrier capacity, the counter is
        // reset to zero and the function unblocks, allowing subsequent code to
        // run.
        pthread_barrier_wait(&barrier);

        printf("Round %d, thread %d\n", round, id);
    }
    
    free(arg);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_barrier_init(
        &barrier,   // Pointer to barrier to initialize
        NULL,       // Barrier configuration; NULL = default
        NUM_THREADS // Number of threads to wait for (barrier capacity)
    );

    pthread_t threads[NUM_THREADS] = {};

    for (int i = 0; i < NUM_THREADS; ++i) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        
        pthread_create(&threads[i], NULL, run_thread, id);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
    
    pthread_barrier_destroy(&barrier);
    return 0;
}
