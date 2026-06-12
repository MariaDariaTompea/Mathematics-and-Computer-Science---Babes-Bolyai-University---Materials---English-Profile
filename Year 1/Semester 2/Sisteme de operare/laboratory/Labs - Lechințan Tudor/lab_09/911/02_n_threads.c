#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *run_thread(void *arg) {
    int *id = (int*)(arg);

    printf("Started thread %d\n", *id);
    sleep(1);
    printf("Finished thread %d\n", *id);

    free(arg);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./02_n_threads <num-threads>\n");
        return 1;
    }

    int num_threads = 0;
    sscanf(argv[1], "%d", &num_threads);

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

        // INCORRECT: The thread that uses this pointer
        // may not have finished using it by this point.
        // free(id);
    }

    sleep(1);

    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    return 0;
}
