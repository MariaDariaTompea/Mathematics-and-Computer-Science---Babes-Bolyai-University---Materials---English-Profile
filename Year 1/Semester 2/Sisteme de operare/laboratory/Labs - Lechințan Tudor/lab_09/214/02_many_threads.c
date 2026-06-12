#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *run_thread(void *arg) {
    sleep(1);
    int *id = (int*)(arg);

    printf("Started thread %d\n", *id);
    printf("Finished thread %d\n", *id);

    // Free the memory we allocated in the main thread.
    free(arg);

    return NULL;
}

// ./02_many_threads <num-threads>
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage:./02_many_threads <num-threads>\n");
        return 1;
    }

    int num_threads = 0;
    sscanf(argv[1], "%d", &num_threads);

    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));

    for (int i = 0; i < num_threads; ++i) {
        // Allocate data to pass to the thread's run function.
        int *id = malloc(sizeof(int));
        *id = i + 1;

        pthread_create(
            &threads[i],
            NULL,
            run_thread,
            id
        );

        // INCORRECT: The thread may not have finished running
        // by the time we free the memory we allocated for it.
        // free(id);
    }

    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    return 0;
}
