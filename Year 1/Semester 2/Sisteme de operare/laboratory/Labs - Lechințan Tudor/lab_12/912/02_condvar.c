#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int stock;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *run_consumer(void *arg) {
    printf("Consumer: started\n");

    pthread_mutex_lock(&mutex);

    for (;;) {
        pthread_cond_wait(&cond, &mutex);

        if (stock > 0) {
            stock -= 1;
            printf("Consumer: consumed %d\n", stock);
            break;
        }
    }

    pthread_mutex_unlock(&mutex);

    printf("Consumer: stopped\n");
    return NULL;
}

void *run_producer(void *arg) {
    sleep(1);

    printf("Producer: started\n");

    pthread_mutex_lock(&mutex);
    stock += 1;
    printf("Producer: produced %d\n", stock);
    pthread_mutex_unlock(&mutex);

    pthread_cond_signal(&cond);

    printf("Producer: stopped\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t consumer = {0};
    pthread_create(
        &consumer,
        NULL,
        run_consumer,
        NULL
    );

    pthread_t producer = {0};
    pthread_create(
        &producer,
        NULL,
        run_producer,
        NULL
    );

    pthread_join(consumer, NULL);
    pthread_join(producer, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
