#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int stock = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *run_consumer(void *arg) {
    printf("Consumer: Hello!\n");

    pthread_mutex_lock(&mutex);
        
    for (;;) { // Guard against spurious wakeups. 
        // Blocks the thread until a signal arrives.
        // Unlocks the mutex while the thread is blocked.
        //
        // After a signal is received the mutex is re-locked.
        // And the thread execution continues.
        pthread_cond_wait(&cond, &mutex);

        if (stock > 0) {
            stock -= 1;
            printf("Consumer: Stock %d\n", stock);
            break;
        }
    }

    pthread_mutex_unlock(&mutex);

    printf("Consumer: Goodbye!\n");
    return NULL;
}

void *run_producer(void *arg) {
    sleep(1);
    printf("Producer: Hello!\n");

    pthread_mutex_lock(&mutex);
    stock += 1;
    printf("Producer: Stock %d\n", stock);
    pthread_mutex_unlock(&mutex);

    // Unblocks a thread waiting on the condvar.
    pthread_cond_signal(&cond);

    printf("Producer: Goodbye!\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t consumer_thread;
    pthread_create(
        &consumer_thread,
        NULL,
        run_consumer,
        NULL
    );

    pthread_t producer_thread;
    pthread_create(
        &producer_thread,
        NULL,
        run_producer,
        NULL
    );

    pthread_join(consumer_thread, NULL);
    pthread_join(producer_thread, NULL);

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);

    return 0;
}
