#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
Make the rounds play in order using barriers.
*/

void *run_skribbl(void *arg) {
    int user_id = *(int*)arg;

    for (int round = 1; round <= 3; ++round) {
        printf("Round %d, user %d\n", round, user_id);
    }

    free(arg);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./03_barrier <users>\n");
        return 1;
    }

    int user_count = 0;
    sscanf(argv[1], "%d", &user_count);
    
    pthread_t *threads = malloc(user_count * sizeof(pthread_t));

    for (int i = 0; i < user_count; ++i) {
        int *user_id = malloc(sizeof(int));
        *user_id = i + 1;

        pthread_create(
            &threads[i],
            NULL,
            run_skribbl,
            user_id
        );
    }

    for (int i = 0; i < user_count; ++i) {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    return 0;
}
