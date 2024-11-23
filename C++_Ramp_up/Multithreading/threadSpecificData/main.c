#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define NUM_THREADS 3
#define TASKS_PER_THREAD 5

// Structure to hold task-specific data
typedef struct {
    int task_id;
    int priority;
    char history[256];
} TaskContext;

// Thread-specific key for storing task context
pthread_key_t task_key;

// Function to log the task action
void log_action(const char *action) {
    TaskContext *context = (TaskContext *)pthread_getspecific(task_key);
    if (context) {
        // Log the action and append it to history
        strncat(context->history, action, sizeof(context->history) - strlen(context->history) - 1);
        strncat(context->history, "; ", sizeof(context->history) - strlen(context->history) - 1);
    } else {
        printf("Logging context is NULL: %s\n", action);
    }
}

// Function to simulate processing a task
void process_task(int task_id) {
    // Simulate some processing time
    sleep(1);
    char action[64];
    snprintf(action, sizeof(action), "Processed Task ID %d", task_id);
    log_action(action);
}

// Worker thread function
void *worker_thread(void *arg) {
    int thread_id = *((int *)arg);
    
    // Create and initialize task context for this thread
    TaskContext *context = malloc(sizeof(TaskContext));
    context->task_id = 0;  // Will be updated in processing
    context->priority = thread_id + 1;  // Assign priority based on thread ID
    context->history[0] = '\0'; // Initialize history

    // Set the thread-specific data
    pthread_setspecific(task_key, context);
    
    // Process a number of tasks
    for (int i = 0; i < TASKS_PER_THREAD; i++) {
        context->task_id = i + 1;  // Update task ID
        process_task(context->task_id);
    }

    // Print task processing history after completion
    printf("Thread %d Task History: %s\n", thread_id, context->history);

    // Cleanup
    free(context);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    
    // Create a key for task-specific data
    if (pthread_key_create(&task_key, free) != 0) {
        perror("pthread_key_create failed");
        return 1;
    }

    int thread_ids[NUM_THREADS] = {1, 2, 3};
    
    // Start worker threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, worker_thread, &thread_ids[i]);
    }
    
    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Delete the key
    pthread_key_delete(task_key);

    return 0;
}