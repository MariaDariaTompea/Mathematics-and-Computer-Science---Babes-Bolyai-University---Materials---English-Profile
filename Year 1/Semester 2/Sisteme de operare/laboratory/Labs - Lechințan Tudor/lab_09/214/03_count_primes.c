#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_MIN 0
#define NUM_MAX 20000000

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

void *compute_primes(void *arg) {
    struct Range *range = (struct Range*)(arg);
    printf("Thread %d - %d..%d\n", range->id, range->from, range->to);

    int prime_counter = 0;
    for (int i = range->from; i < range->to; ++i) {
        if (is_prime(i)) {
            prime_counter += 1;
        }
    }

    printf("Thread %d finished: %d primes\n", range->id, prime_counter);
    free(arg);
    return NULL; 
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./03_performance <num-threads>\n");
        return 1;
    }

    int num_threads = 0;
    sscanf(argv[1], "%d", &num_threads);

    if (num_threads < 1) {
        printf("Usage: ./03_performance <num-threads>\n");
        return 1;
    }

    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));

    int from = 0;
    int num_per_thread = NUM_MAX / num_threads;

    for (int i = 0; i < num_threads; ++i) {
        struct Range *range = malloc(sizeof(struct Range));
        range->id = i + 1;
        range->from = from;
        range->to = from + num_per_thread;

        pthread_create(
            &threads[i],
            NULL,
            compute_primes,
            range
        );

        from = range->to;
    }

    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    return 0;
}
