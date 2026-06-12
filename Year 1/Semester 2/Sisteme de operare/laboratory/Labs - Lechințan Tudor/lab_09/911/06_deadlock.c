#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t mutex1, mutex2;

void *run_thread_a(void *arg) {
    printf("Started thread A\n");

    pthread_mutex_lock(&mutex1);
    sleep(1);
    pthread_mutex_lock(&mutex2);

    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);

    printf("Finished thread A\n");
    return NULL;
}

void *run_thread_b(void *arg) {
    printf("Started thread B\n");

    pthread_mutex_lock(&mutex2);
    sleep(1);
    pthread_mutex_lock(&mutex1);

    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);

    printf("Finished thread B\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);

    pthread_t thread_a = {0};
    pthread_create(
        &thread_a,
        NULL,
        run_thread_a,
        NULL
    );

    pthread_t thread_b = {0};
    pthread_create(
        &thread_b,
        NULL,
        run_thread_b,
        NULL
    );

    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);

    return 0;
}
