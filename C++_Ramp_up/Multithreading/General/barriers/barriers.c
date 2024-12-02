#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

/*
    Barrier
    Syncronization mechanism that allow multiple threads to wait for each other to reach
    a certain point in execution.
    When threads reach the barrier, they are blocked until all expected threads reached it.

*/

#define NUM_THREADS 4
pthread_barrier_t barrier;

void* thread_function(void* arg) {
    int id = *((int*)arg);
    printf("Thread %d: starting work...\n", id);
    
    // Simulate some work by sleeping
    sleep(rand() % 3 + 1);

    printf("Thread %d: reaching barrier...\n", id);
    // Wait at the barrier
    pthread_barrier_wait(&barrier);
    
    printf("Thread %d: crossed barrier\n", id);
    
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize the barrier
    pthread_barrier_init(&barrier, NULL, NUM_THREADS);
    
    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, (void*)&thread_ids[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the barrier
    pthread_barrier_destroy(&barrier);
    
    printf("All threads completed their tasks.\n");
    return 0;
}