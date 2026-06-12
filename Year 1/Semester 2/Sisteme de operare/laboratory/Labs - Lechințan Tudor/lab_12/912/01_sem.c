#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_THREADS 10
#define SEM_CAPACITY 5

int counter;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t sem;

/*
sem_t sem
sem_init(&sem, 0, capacity)
sem_destroy(&sem)
sem_wait(&sem)
sem_post(&sem)
*/

void *run_thread(void *arg) {
    int temp_counter = 0;

    sem_wait(&sem);

    pthread_mutex_lock(&mutex);
    counter += 1;
    temp_counter = counter;
    pthread_mutex_unlock(&mutex);

    // Simulate heavy work...
    printf("Threads doing work: %d\n", temp_counter);
    sleep(1);

    pthread_mutex_lock(&mutex);
    counter -= 1;
    pthread_mutex_unlock(&mutex);

    sem_post(&sem);

    free(arg);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t threads[NUM_THREADS];
    sem_init(&sem, 0, SEM_CAPACITY);
        
    for (int i = 0; i < NUM_THREADS; ++i) {
        int *id = malloc(sizeof(int));
        *id = i;

        pthread_create(
            &threads[i],
            NULL,
            run_thread,
            id
        );
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem);

    return 0;
}
