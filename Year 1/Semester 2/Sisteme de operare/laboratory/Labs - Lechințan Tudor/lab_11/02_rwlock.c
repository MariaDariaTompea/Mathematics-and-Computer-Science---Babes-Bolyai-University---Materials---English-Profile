#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
Replace the mutex with a rwlock.

Use:
    - PTHREAD_RWLOCK_INITIALIZERV
    - pthread_rwlock_rdlock
    - pthread_rwlock_wrlock
    - pthread_rwlock_unlock
*/

#define BUF_SIZE 128

char buf[BUF_SIZE];
pthread_mutex_t buf_mutex = PTHREAD_MUTEX_INITIALIZER;

// Arg is a thread ID.
void *run_thread(void *arg) {
    int id = *(int*)(arg);

    for (;;) {
        pthread_mutex_lock(&buf_mutex);
        if (strcmp(buf, "exit") == 0) {
            break;
        }

        printf("Thread %d: %s\n", id, buf);
        pthread_mutex_unlock(&buf_mutex);

        sleep(3);
    }

    free(arg);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./02_rwlock <thread_count>\n");
        return 1;
    }

    int thread_count = 0;
    sscanf(argv[1], "%d", &thread_count);

    pthread_t *threads = malloc(thread_count * sizeof(pthread_t));

    for (int i = 0; i < thread_count; ++i) {
        int *id = malloc(sizeof(int));
        *id = i;

        pthread_create(
            &threads[i],
            NULL,
            run_thread,
            id
        );
    }

    char inputted_string[BUF_SIZE] = {0};

    for (;;) {
        printf("Input a string\n");
        scanf("%s", inputted_string);

        if (strcmp(inputted_string, "exit") == 0) {
             break;
        }

        pthread_mutex_lock(&buf_mutex);
        strcpy(buf, inputted_string);
        pthread_mutex_unlock(&buf_mutex);
    }

    for (int i = 0; i < thread_count; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
