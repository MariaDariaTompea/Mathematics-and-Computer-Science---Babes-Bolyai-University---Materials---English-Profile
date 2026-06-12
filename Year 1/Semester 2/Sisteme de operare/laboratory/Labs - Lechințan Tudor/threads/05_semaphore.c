#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_ITERATIONS 3
#define NUM_THREADS 6
#define SEMAPHORE_PERMITS 2

// Semaphores hold an internal counter that tracks how many threads are allowed
// to access a region of code. The initial value of the internal counter is set
// when creating the semaphore.
sem_t sem;

void *run_thread(void *arg) {
    int id = *(int*)arg;
    
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        // Blocks if the internal counter is zero.
        //
        // If the internal counter is greater than zero, the counter is
        // decremented and subsequent code can be executed.
        sem_wait(&sem);

        printf("Thread %d, iteration %d\n", id, i);
        sleep(1);

        // Increments the internal counter, allowing another thread to access
        // the code protected by the semaphore.
        sem_post(&sem);
    }
    
    free(arg);
    return NULL;
}

int main(int argc, char *argv[]) {
    sem_init(
        &sem,             // Pointer to semaphore to initialize
        0,                // Whether to share the semaphore with other processes; 0 = NO
        SEMAPHORE_PERMITS // Number of threads that can access the code symultaneously
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
    
    sem_destroy(&sem);
    return 0;
}
