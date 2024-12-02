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
To support the "Pthreads" (POSIX threads) standard, the following hardware operations are generally necessary, particularly to implement synchronization primitives like mutexes and condition variables efficiently:
1. Atomic Operations: The hardware must support atomic operations to manipulate memory safely in concurrent contexts. This typically includes:
    * Atomic Test-and-Set: Used to change the state of a lock in one uninterruptible operation.
    * Atomic Compare-and-Swap (CAS): Used to implement more complex, lock-free data structures and synchronization mechanisms.
2. Memory Barriers (Fences): These operations ensure memory operations are completed in a specified order. They're used to prevent reordering by the compiler or CPU, 
    which is crucial for ensuring that changes made by one thread are visible to others appropriately.
3. Timer and Interrupt Support: Support for timers and handling interrupts are critical for implementing thread scheduling, context switching, and sleep/wake mechanisms.
4. Context Switching: The ability to save and load CPU register states efficiently so that the execution of one thread can be paused and another resumed. This is typically 
    more related to the operating system’s role but is highly dependent on CPU capabilities and features like interrupt handling and mode switching.
5. Cache Coherency Mechanisms: In multi-core systems, ensuring cache coherence so that changes in one core’s cache are reflected across other cores is important 
    to maintain data consistency for shared data among threads.

These hardware features are leveraged by the operating system and threading libraries (like Pthreads) to provide thread management, 
synchronization, and scheduling capabilities effectively. While the exact implementation details can vary based on architecture and operating system, 
these features are fundamental building blocks for supporting the efficient, safe execution of multiple threads in parallel.

Memory barriers in pthread standard:
Where are memory barriers used in pthreads standard?
1. Mutexes:
    * When a thread acquires or releases a mutex using pthread_mutex_lock() or pthread_mutex_unlock(), memory barriers are used to ensure that all memory operations (reads and writes) that occurred before the lock is unlocked are visible to all threads that subsequently acquire that lock.
    * This guarantees that any data modified while a mutex is held is correctly seen by another thread that later acquires that same mutex.
2. Condition Variables:
    * In pthread_cond_wait() and pthread_cond_signal(), memory barriers are used to ensure that changes made to shared variables are visible to other threads. For instance, when a thread waits on a condition variable, it must release the associated mutex and ensure that all changes made to shared data are visible before it waits.
    * Conversely, when signaling a condition variable with pthread_cond_signal(), the memory barrier ensures that any prior writes made by the signaling thread are visible to the thread that receives the signal.
*/

/*  
    Thread local storage (memory globally available in the contex of a single thread)
    Memory isn't shared with other threads.
    Each thread has a clear and isolated context, which enhances data integrity and clarity
    Using TLS threads create private copies of data, access its own version based on key.
    Especially helpful for complex call chains where passing information is challenging.
*/

/*
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
        Priority inversion: A lower priority thread hold a lock required by a higher priority thread, causing the last one to wait.
                            Can be mitigated using priority inheritance of priority ceiling protocols
        Inefficient data sharing: Excesive data sharing between threads can lead to bottlenecks. Minimize sharing and use fine-grained locking to reduce contention and
                                  improve concurrency execution.
                                  Excesive data sharing brings high contention on mutex. When multiple threads try to aquire a mutex only one will succed, the rest
                                  will be waiting, loosing the opportunity to concurrency execution. Also locking and unlocking a mutex brings additional overhead
                                  because of the need to manage the synchronization primitives
                                  An option to sharing data is using Lock-free data structures (TODO).                                 
*/

/* 
    Recursive mutex (prevents deadlocks in case of recursive function call)
        When are they useful?
            1. When a function is called recursively
            2. When a function call another function that needs the same lock
        
*/

/*
    pthread_once
        Pthread_once execute make a single call to given routine inside thread.
        First thread scheduled to execute the function will call the routine.
        After this no other thread will be able to call the routine.
        It is used mainly for initialization code (like in the current application),
        sharing resources across threads (files, shared libs etc)    
*/

/*
    Thread attributes:
        There are 3 main attributes a thread can have:
        1. Stack size
        2. Stack location
        3. Detached or not

        Stack size and location are usefull especially in the embedded systems or when you want to 
        have complet control over the stack. You can check that the stack is big enough and 
        doesn't overlap with stacks of other execution threads.  
*/

/*
    Threads scheduling
    In real time systems some threads are more important than others, so you want to increase their priority.
    The scheduler compares the priorities of all runnable threads of all processes systemwide when selecting
    a thread to run on an available CPU. It chooses the thread with highest priority regardless the process 
    it belongs to.
    Scheduling policies:
        - FIFO (Let a thread run until it either calls exits or blocks).
          Once it unblocks, it is put in the last place in priority queue.
        - Round-Robin (Thread is interrupted after a fixed amount of time)
*/

/*
    Priority inversion principle (bounded and unbounded)
        Task 1 (low priority) runs and locks resource
        Task 2 (high priority) gets into runnable state but needs that resource, it has to wait until the low priority
               task releases the lock
        Task 3 (medium priority) meanwhile, while task 2 is waiting, task 3 (which doesn't need the resource) preempts the task 1 because it has a higher
               priority and now Task 2 waits for both task 1 and task 3.

    Solutions:
        Priority ceiling protocol:
            A task can lock a resource only if its priority is higher than the current system ceiling, which is defined as the highest of 
            all the priority ceilings of resources currently held by any task. If a higher priority task comes along while a resource is 
            held by a lower-priority task, the lower-priority task temporarily inherits the higher priority to prevent other tasks 
            (of intermediate priority) from running and potentially causing priority inversion. 
            Therefore, the higher-priority task does not interrupt the lower-priority task immediately if the 
            lower-priority task holds the lock on the needed resource. Instead, PCP elevates the lower-priority task's 
            priority to ensure it can complete and release the lock, allowing the higher-priority task to eventually proceed.

        Priority inheritance:
            The low priority task inherits the priority of the blocking high priority task in order to prevent another 
            medium priority task that doesn't need the resource to run before high priority task

*/

/* 
    TO DO:
        - Lock-free data structure                
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
pthread_once_t gOnceCntrlVar = PTHREAD_ONCE_INIT;
void *gStackStartAddr;
int const gStackSize = 1024 * 1024;

void Destruct(void* arg)
{
    printf("Destruct called\n");
    free(arg);
}

void initResources()
{
    // Whenever a thread exits "Destruct"" function is called for each data that was set with "pthread_setspecific"
    pthread_key_create(&gKey, Destruct);    

    for(int i=0; i<MAX_NR_OF_ENTRIES; ++i)
    {
        pthread_mutex_init(&gInBuffer.mMutex, NULL);
        pthread_mutex_init(&gOutBuffer.mMutex, NULL);
    }
}

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
    return rand() % 10;
}



static void AddToOutpBuffer(int aResp)
{
    /*
        Locking and unlocking a mutex, at the lowest level it is implemented using an atomic hw operation, like CAS (compare and swap)
        or test and set. Example of mutex implementation:
        // Mutex implementation:
        ============================
        while (true) {
        if (test_and_set(&lock) == 0) {
            break;  // Lock acquired successfully
        }
        // Optionally, yield CPU, sleep, or perform other operations before retrying
        }
        //test _and_set is an atomic operation

        There are also read/write mutexes, comes as an optimization over traditional ones. 
       The primary purposes of a read/write lock are to improve performance by allowing multiple readers to access a resource simultaneously 
       while ensuring that only one writer can modify the resource at any given time.
    */
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
    pthread_once(&gOnceCntrlVar, initResources);

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
    pthread_attr_t lAttr;
    pthread_t lArrayOfThreads[NR_OF_THREADS];
    srand(time(NULL));

    gStackStartAddr = malloc(sizeof(gStackSize));
    pthread_attr_init(&lAttr);
    // pthread_attr_setstacksize(&lAttr, gStackSize);
    pthread_attr_setstack(&lAttr, gStackStartAddr, gStackSize);

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
    free(gStackStartAddr);
    pthread_attr_destroy(&lAttr);

}