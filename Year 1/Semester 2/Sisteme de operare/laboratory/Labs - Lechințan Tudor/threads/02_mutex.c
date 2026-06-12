#include <pthread.h>
#include <stdio.h>

#define NUM_INCREMENTS 1000000
#define NUM_THREADS 2

int counter = 0;

// Mutexes can have 2 states: unlocked and locked.
pthread_mutex_t mutex;

void *run_thread(void *arg) {
    for (int i = 0; i < NUM_INCREMENTS; ++i) {
        // If the mutex is locked, this function blocks until the mutex is
        // unlocked.
        //
        // If the mutex is unlocked, this function locks the mutex and allows
        // subsequent code to run.
        pthread_mutex_lock(&mutex);

        // This line performs 3 operations:
        // 1. Reading the counter from memory into a temporary variable.
        // 2. Incrementing the temporary variable.
        // 3. Writing the new value back into memory.
        //
        // When using multiple threads without synchronization, the final
        // result will be incorrect. The solution is to use a mutex.
        counter += 1;

        // Unlocks the mutex, allowing other threads to lock the mutex.
        pthread_mutex_unlock(&mutex);
    }
    
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_mutex_init(
        &mutex, // Pointer to mutex to initialize
        NULL    // Mutex configuration; NULL = default
    );

    pthread_t threads[NUM_THREADS] = {};

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, run_thread, NULL);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex);

    printf("Counter: %d\n", counter);
    return 0;
}
