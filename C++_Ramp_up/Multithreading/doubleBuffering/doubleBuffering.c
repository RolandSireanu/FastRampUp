#include "pthread.h"
#define _GNU_SOURCE
#include "pthread.h"
#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

/*
    Thread local storage (memory globally available in the contex of a single thread)
    Memory isn't shared with other threads.
    Each thread has a clear and isolated context, which enhances data integrity and clarity

    Pitfalls in multithreaded programming:
        Race conditions: Occurs when multiple threads access shared data and at least one of thme modifies it without a proper
                         syncronization.
                         At a fundamental level, the race condition reduces to "Read/Modify/Write" problem.
                         Thread 1 reads value, Thread 2 modifies it, Thread 1 modifies it again => data is corrupted
        
        Deadlocks (deadly embrace): Happens when two threads are waiting for each other to release locks on the same mutex.
                                    To avoid this, always ensure that in all functions executed by threads (like t1 and t2)
                                    the program aquire locks in the same order.
                                    Example:
                                        void t1(void*){ pthread_mutex_lock(&lock1); ... pthread_mutex_lock(&lock2) ... }
                                        void t1(void*){ pthread_mutex_lock(&lock2); ... pthread_mutex_lock(&lock1) ... }
                                    


*/


#define NR_OF_THREADS       20
#define MAX_NR_OF_ENTRIES   1024

typedef struct Request
{    
    int mStartInterval;
    int mEndInterval;
}Request_t;

typedef struct InBuffer
{
    Request_t mBuffer[MAX_NR_OF_ENTRIES];
    pthread_mutex_t mMutex;
    int mFirstFreePos;
    int mNrOfEntries;
}InBuffer_t;

typedef struct OutBuffer
{
    int mBuffer[MAX_NR_OF_ENTRIES];
    pthread_mutex_t mMutex;
    int mFirstFreePos;
    int mNrOfEntries;
}OutBuffer_t;

InBuffer_t gInBuffer;
OutBuffer_t gOutBuffer;
pthread_cond_t  gCondInputAvailable = PTHREAD_COND_INITIALIZER;
pthread_cond_t  gCondSpaceInInput = PTHREAD_COND_INITIALIZER;
pthread_cond_t gCondSpaceInOutput = PTHREAD_COND_INITIALIZER;
pthread_cond_t gCondOutBufferAvailable = PTHREAD_COND_INITIALIZER;
pthread_key_t gKey;
static int isPrime(int num) {
    if (num <= 1) 
    {
        return 0;
    }
    if (num <= 3) 
    {
        return 1;
    }

    for(int i=2; i<num; ++i)
    {
        if(num % i == 0)
        {
            return 0;
        }
    }

    return 1;
}

static int SumPrimeNumbers() 
{
    int sum = 0;
    Request_t lReq = *((Request_t*)pthread_getspecific(gKey));

    for (int i = lReq.mStartInterval; i <= lReq.mEndInterval; ++i)
    {
        if (isPrime(i) == 1) 
        {
            sum += i;
        }
    }
    return sum;
}

static int inline GenEndInterval()
{
    return rand() % 10000;
}

void Destruct(void* arg)
{
    printf("Destruct called\n");
    free(arg);
}

static void AddToOutpBuffer(int aResp)
{
    pthread_mutex_lock(&gOutBuffer.mMutex);    
    while(gOutBuffer.mNrOfEntries == MAX_NR_OF_ENTRIES)
    {
        // A condition variable is just a syncronization point between threads.
        // Threads are put on sleep until a specific signal come
        // Condition variable often leverage futexes (mutex in user space)
        // Why are condition variables important? They eliminate the constant pooling issue.
        pthread_cond_wait(&gCondSpaceInOutput, &gOutBuffer.mMutex);
    }
    
    if(gOutBuffer.mFirstFreePos < MAX_NR_OF_ENTRIES-1)
    {
        gOutBuffer.mBuffer[gOutBuffer.mFirstFreePos] = aResp;    
        gOutBuffer.mFirstFreePos++;
        gOutBuffer.mNrOfEntries++;
    }
    
    /*
        Why would I call pthread_cond_signal when pthread_cond_broadcast is a superset of the first one?
            - Express intent clearer, improve readability and maintainability of your code
            - Avoid unnecessary wake-ups, when all threads are awakened, they all try to reaquire the mutex
              which leads to context switching and unnecessary overhead.
    */
    pthread_cond_broadcast(&gCondOutBufferAvailable);
    pthread_mutex_unlock(&gOutBuffer.mMutex);
}

static int GetFromOutBuffer()
{
    int lResp;

    pthread_mutex_lock(&gOutBuffer.mMutex);
    while(gOutBuffer.mNrOfEntries == 0)
        pthread_cond_wait(&gCondOutBufferAvailable, &gOutBuffer.mMutex);
    
    if(gOutBuffer.mFirstFreePos > 0)
    {
        lResp = gOutBuffer.mBuffer[gOutBuffer.mFirstFreePos-1];
        gOutBuffer.mFirstFreePos--;
        gOutBuffer.mNrOfEntries--;
    }
    
    pthread_cond_broadcast(&gCondSpaceInOutput);
    pthread_mutex_unlock(&gOutBuffer.mMutex);
    
    return lResp;
}

static void AddToInputBuffer(Request_t aReq)
{
    pthread_mutex_lock(&gInBuffer.mMutex);    
    while(gInBuffer.mNrOfEntries == MAX_NR_OF_ENTRIES)
    {
        pthread_cond_wait(&gCondSpaceInInput, &gInBuffer.mMutex);
    }
    
    if(gInBuffer.mFirstFreePos < (MAX_NR_OF_ENTRIES - 1) && gInBuffer.mNrOfEntries < (MAX_NR_OF_ENTRIES-1))
    {
        gInBuffer.mBuffer[gInBuffer.mFirstFreePos] = aReq;
        gInBuffer.mFirstFreePos++;
        gInBuffer.mNrOfEntries++;
    }
        
    pthread_cond_broadcast(&gCondInputAvailable);
    pthread_mutex_unlock(&gInBuffer.mMutex);
}

static Request_t GetFromInBuffer()
{
    Request_t lReq;

    pthread_mutex_lock(&gInBuffer.mMutex);
    while(gInBuffer.mNrOfEntries == 0)
    {
        pthread_cond_wait(&gCondInputAvailable, &gInBuffer.mMutex);
    }

    if(gInBuffer.mFirstFreePos > 0)
    {
        lReq = gInBuffer.mBuffer[gInBuffer.mFirstFreePos-1];
        gInBuffer.mFirstFreePos--;
        gInBuffer.mNrOfEntries--;        
    }

    pthread_cond_broadcast(&gCondSpaceInInput);
    pthread_mutex_unlock(&gInBuffer.mMutex);

    return lReq;
}

void* Thread(void* arg)
{
    Request_t* lPtrReq = (Request_t*)malloc(sizeof(Request_t));
    while(1)
    {   
        Request_t lReq = GetFromInBuffer();        
        *lPtrReq = lReq;

        pthread_setspecific(gKey, lPtrReq);
        int lResp = SumPrimeNumbers();
        // printf("Start/EndInterval = [%d - %d]   SumPrimeNumbers = %d\n", lReq.mStartInterval, lReq.mEndInterval, lResp);
        AddToOutpBuffer(lResp);        
    }

    pthread_exit(NULL);
}

int main()
{
    int lId = 0;
    pthread_t lArrayOfThreads[NR_OF_THREADS];
    srand(time(NULL));

    // Whenever a thread exits "Destruct"" function is called for each data that was set with "pthread_setspecific"
    pthread_key_create(&gKey, Destruct);

    for(int i=0; i<MAX_NR_OF_ENTRIES; ++i)
    {
        pthread_mutex_init(&gInBuffer.mMutex, NULL);
        pthread_mutex_init(&gOutBuffer.mMutex, NULL);
    }

    for(int i=0; i<NR_OF_THREADS; ++i)
    {
        int lEndInterval = GenEndInterval();
        Request_t lTempReq = {.mStartInterval=0, .mEndInterval = lEndInterval};
        lId++;
        AddToInputBuffer(lTempReq);
    }

    for(int i=0; i<NR_OF_THREADS; ++i)
    {
        pthread_create(&lArrayOfThreads[i], NULL, Thread, NULL);
    }

    while(1)
    {
        for(int i=0; i<NR_OF_THREADS; ++i)
        {
            int lEndInterval = GenEndInterval();
            Request_t lTempReq = {.mStartInterval=0, .mEndInterval = lEndInterval};
            lId++;
            AddToInputBuffer(lTempReq);    
        }
        
        printf("Response sum = %d\n", GetFromOutBuffer());
    }

    for(int i=0; i<NR_OF_THREADS; ++i)
    {
        pthread_join(lArrayOfThreads[i], NULL);
    }

    pthread_key_delete(gKey);    
}