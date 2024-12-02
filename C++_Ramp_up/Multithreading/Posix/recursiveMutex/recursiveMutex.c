#include "pthread.h"
#define _GNU_SOURCE
#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"

/*
    Recursive mutex
    Type of mutex that allows the same thread to lock it multiple times without causing a deadlock.
    Maintain a lock count and allow the same thread to reacquire the lock safely.
    When a thread tries to lock a recursive mutex, it checks if the current thread is already the owner. It it is it allows the locking and
    increment the lock counter.
    When thread unlocks the mutex, the counter decrements.
    Only when counter reaches 0 the mutex is available for other thread.
*/

pthread_mutex_t gRecursiveMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t gRecursiveThread;
int gNrOfIterations = 10;

void f(int depth)
{
    if(depth == 0)
        return;

    pthread_mutex_lock(&gRecursiveMutex);
    // Do some work 
    printf("Working ... %d\n", gNrOfIterations--);    
    f(depth - 1);
    pthread_mutex_unlock(&gRecursiveMutex);
}

void* recursiveF(void*)
{
    f(10);
    return NULL;
}

int main()
{
    pthread_mutexattr_t lAttr;
    pthread_mutexattr_init(&lAttr);
    pthread_mutexattr_settype(&lAttr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&gRecursiveMutex, &lAttr);

    pthread_create(&gRecursiveThread, NULL, recursiveF, NULL);
    pthread_join(gRecursiveThread, NULL);

    pthread_attr_destroy(&lAttr);
    pthread_mutex_destroy(&gRecursiveMutex);
    pthread_cancel(gRecursiveThread);

    return 0;
}

