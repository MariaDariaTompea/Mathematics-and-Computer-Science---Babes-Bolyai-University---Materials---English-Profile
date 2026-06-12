#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ROUND_COUNT 3
int num_threads;

/*
Use a barrier to have the players play the same round.

Use:
    - pthread_barrier_init(handle, NULL, capacity)
    - pthread_barrier_destroy
    - pthread_barrier_wait
*/

void *run_thread(void *arg) {
    int thread_id = *(int*)arg;

    for (int round = 1; round <= ROUND_COUNT; ++round) {
        printf("Playing round %d, player %d\n", round, thread_id);
    }

    free(arg);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./01_barrier <num_players>\n");
        return 1; 
    }

    sscanf(argv[1], "%d", &num_threads);

    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));

    for (int i = 0; i < num_threads; ++i) {
        int *thread_id = malloc(sizeof(int));
        *thread_id = i;

        pthread_create(
            &threads[i],
            NULL,
            run_thread,
            thread_id
        );
    }

    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    return 1;
}
