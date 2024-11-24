#include "pthread.h"
#define _GNU_SOURCE
#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "semaphore.h"
#include "time.h"
#include <stdlib.h>
#include <stdio.h>

/*
    Semaphores
    Syncronization tools over a common resource.
    Helpfull when you want to restrict the number of threads that can access a resource.
    In our example, we don't have to check for access boundaries inside gQueue because
    there are only MAX_NO_ENTRIES threads that can add/remove jobs from queue

    Semaphores have low boundary check (doesn't decrease below 0) but not high boundary (can increase infinitly)
    Semaphore maintains a count that indicates how many threads can acquire it.
    Every sem_wait deacreses the counter, every sem_post increases the counter

    In a producer-consumer problem, semaphores can be used to ensure that the producer does 
    not add items to a full buffer and that the consumer does not remove items from an empty buffer.
    Using semaphores effectively helps prevent race conditions and ensures data integrity in concurrent applications.

*/

#define NR_OF_THREADS   8
#define MAX_NO_ENTRIES  4
sem_t gQueueEnter;
sem_t gMutex;
sem_t gAvailableJobs;
int gQueue[MAX_NO_ENTRIES];
int gCounter = 0;

void* producer(void* arg)
{
    while(1)
    {        
        sem_wait(&gQueueEnter);
        // MAX_NF_OF_ENTRIES will pass
        sem_wait(&gMutex);
        // Mutual exclusion zone
        gQueue[gCounter] = (rand() % 100);
        gCounter++;
        sem_post(&gMutex);
        sem_post(&gAvailableJobs);
    }

    return NULL;
}

void* consumer(void* arg)
{
    while(1)
    {           
        sem_wait(&gAvailableJobs);
        sem_wait(&gMutex);
        printf("Job in Q with id = %d and value %d\n", gCounter, gQueue[gCounter-1]);
        gCounter--;
        sem_post(&gMutex);        
        sem_post(&gQueueEnter);        
    }
}

int main()
{
    pthread_t lProducerThreads[NR_OF_THREADS];
    pthread_t lConsumerThreads[NR_OF_THREADS];

    srand(time(NULL));

    // Binary semaphore
    sem_init(&gMutex, 0, 1);
    sem_init(&gQueueEnter, 0, MAX_NO_ENTRIES);
    sem_init(&gAvailableJobs, 0, 0);

    for(int i=0; i<NR_OF_THREADS; ++i)
    {
        pthread_create(&lProducerThreads[i], NULL, producer, NULL);
        pthread_create(&lConsumerThreads[i], NULL, consumer, NULL);
    }

    for(int i=0; i<NR_OF_THREADS; ++i)
    {
        pthread_join(lProducerThreads[i], NULL);
        pthread_join(lConsumerThreads[i], NULL);
    }
    

}

