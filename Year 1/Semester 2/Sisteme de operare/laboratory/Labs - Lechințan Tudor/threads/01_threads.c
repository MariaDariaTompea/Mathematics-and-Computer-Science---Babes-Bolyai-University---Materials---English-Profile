#include <pthread.h> // pthread_*
#include <stdio.h>   // printf
#include <stdlib.h>  // malloc, free

void *run_thread(void *arg) {
    // Extract the concrete value from the argument.
    int arg_value = *(int*)arg;

    printf("Thread received: %d\n", arg_value);

    // Allocate memory for the return value.
    int *return_value = malloc(sizeof(int));

    // Compute the return value.
    *return_value = arg_value + 2;

    // Free the argument after we are done using it.
    free(arg);

    return return_value;
}

int main(int argc, char *argv[]) {
    pthread_t thread = {};

    // Allocate memory for the thread argument.
    int *thread_arg = malloc(sizeof(int));

    *thread_arg = 67;

    // Create a new thread that will run in parallel with our
    // main thread.
    pthread_create(
        &thread,    // Pointer to a thread handle
        NULL,       // Thread configuration; NULL == default
        run_thread, // Function to run in the newly created thread
        thread_arg  // Argument passed to the function
    );

    // Pointer in which the thread's return value will be stored.
    int *thread_return_value = NULL;

    // Block until the thread finishes its execution.
    // 
    // We can pass NULL as the second argument if we don't
    // care about the return value, but in our case we do
    // care so we will pass a non-NULL pointer.
    pthread_join(thread, (void**)&thread_return_value);

    printf("Thread returned: %d\n", *thread_return_value);

    // Free the value allocated by the thread.
    free(thread_return_value);
    
    return 0;
}
