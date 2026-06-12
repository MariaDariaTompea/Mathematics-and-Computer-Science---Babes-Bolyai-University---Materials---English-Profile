#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_MIN 0
#define NUM_MAX 20000000

int total = 0;
pthread_mutex_t mutex;

struct Range {
    int id, from, to;
};

int is_prime(int num) {
    if (num == 2) {
        return 1;
    }

    if (num < 2 || num % 2 == 0) {
        return 0;
    }

    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0) {
            return 0;
        }
    }

    return 1;
}

void *run_prime_counter(void *arg) {
    struct Range *range = (struct Range*)(arg);
    printf("Thread %d - %d..%d\n", range->id, range->from, range->to);

    int counter = 0;
    for (int i = range->from; i < range->to; ++i) {
        if (is_prime(i)) {
            counter += 1;
        }
    }

    printf("Thread %d found %d primes\n", range->id, counter);

    // When multiple threads write to the same variable access
    // must be protected by a mutex.
    pthread_mutex_lock(&mutex);
    total += counter;
    pthread_mutex_unlock(&mutex);

    free(arg);
    return NULL; 
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage ./03_count_primes <num-threads>\n");
        return 1;
    }

    int num_threads = 0;
    sscanf(argv[1], "%d", &num_threads);

    pthread_mutex_init(&mutex, NULL);

    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    int from = NUM_MIN;
    int count = NUM_MAX / num_threads;

    for (int i = 0; i < num_threads; ++i) {
        struct Range *range = malloc(sizeof(struct Range));
        range->id = i;
        range->from = from;
        range->to = from + count;

        pthread_create(
            &threads[i],
            NULL,
            run_prime_counter,
            range
        );

        from += count;
    }

    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("Total: %d\n", total);

    pthread_mutex_destroy(&mutex);

    free(threads);
    return 0;
}
