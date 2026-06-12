#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int num;
pthread_rwlock_t mutex = PTHREAD_RWLOCK_INITIALIZER;

void *run_thread(void *arg) {
    int thread_id = *(int*)arg;

    for (;;) {
        pthread_rwlock_rdlock(&mutex);

        printf("Thread %d, num: %d\n", thread_id, num);
        sleep(3);

        if (num == -1) {
            pthread_rwlock_unlock(&mutex);
            break;
        }

        pthread_rwlock_unlock(&mutex);
        sleep(1);
    }

    free(arg);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./01_mutex <num_threads>\n");
        return 1; 
    }

    int num_threads;
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
    
    for (;;) {
        printf("Please input a number\n");

        int temp;
        scanf("%d", &temp);

        pthread_rwlock_wrlock(&mutex);
        num = temp;
        pthread_rwlock_unlock(&mutex);

        if (temp == -1) {
            break;
        }
    }

    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    return 1;
}
