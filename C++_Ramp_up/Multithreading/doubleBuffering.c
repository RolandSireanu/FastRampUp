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

#define NR_OF_THREADS       24
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

int isPrime(int num) {
    if (num <= 1) 
    {
        return 0;
    }
    if (num <= 3) 
    {
        return 1; // 2 and 3 are prime numbers
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

int Sum(int start, int end) 
{
    int sum = 0;
    for (int i = start; i <= end; ++i) 
    {
        if (isPrime(i) == 1) 
        {
            sum += i;
        }
    }
    return sum;
}

void AddToOutpBuffer(int aResp)
{
    pthread_mutex_lock(&gOutBuffer.mMutex);
    // If first free position is < MAX_NR_OF_ENTRIES => there is still space in gOutBuffer
    while(gOutBuffer.mNrOfEntries == MAX_NR_OF_ENTRIES)
    {
        pthread_cond_wait(&gCondSpaceInOutput, &gOutBuffer.mMutex);
    }
    
    // Add aResp to gOutBuffer on the first free position    
    if(gOutBuffer.mFirstFreePos < MAX_NR_OF_ENTRIES-1)
    {
        gOutBuffer.mBuffer[gOutBuffer.mFirstFreePos] = aResp;
        // Increment next free position in gOutBuffer
        gOutBuffer.mFirstFreePos++;
        gOutBuffer.mNrOfEntries++;
    }
    
    pthread_cond_broadcast(&gCondOutBufferAvailable);
    pthread_mutex_unlock(&gOutBuffer.mMutex);
}

int GetFromOutBuffer()
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

void AddToInputBuffer(Request_t aReq)
{
    pthread_mutex_lock(&gInBuffer.mMutex);
    // If first free position in buffer is < MAX_NR_OF_ENTRIES => there is still space in gOutBuffer
    while(gInBuffer.mNrOfEntries == MAX_NR_OF_ENTRIES)
    {
        // If buffer is full => wait in SpaceInInput condition
        pthread_cond_wait(&gCondSpaceInInput, &gInBuffer.mMutex);
    }
    
    if(gInBuffer.mFirstFreePos < (MAX_NR_OF_ENTRIES - 1))
    {
        gInBuffer.mBuffer[gInBuffer.mFirstFreePos] = aReq;
        gInBuffer.mFirstFreePos++;
        gInBuffer.mNrOfEntries++;
    }
    
    printf("Nr of entries in input buffer %d\n", gInBuffer.mNrOfEntries);
    pthread_cond_broadcast(&gCondInputAvailable);
    pthread_mutex_unlock(&gInBuffer.mMutex);
}

Request_t GetFromInBuffer()
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
    while(1)
    {   
        Request_t const lReq = GetFromInBuffer();
        int lResp = Sum(lReq.mStartInterval, lReq.mEndInterval);
        printf("Start/EndInterval = [%d - %d]   Sum = %d\n", lReq.mStartInterval, lReq.mEndInterval, lResp);
        AddToOutpBuffer(lResp);
    }
    return NULL;
}

int main()
{
    int lId = 0;
    pthread_t lArrayOfThreads[NR_OF_THREADS];
    srand(time(NULL));   // Initialization, should only be called once

    for(int i=0; i<NR_OF_THREADS; ++i)
    {
        Request_t lTempReq = {.mStartInterval=0, .mEndInterval = rand() % 100000};
        lId++;
        AddToInputBuffer(lTempReq);
    }

    for(int i=0; i<NR_OF_THREADS; ++i)
    {
        pthread_create(&lArrayOfThreads[i], NULL, Thread, NULL);
    }

    while(1)
    {
        for(int i=0; i<NR_OF_THREADS/10; ++i)
        {
            Request_t lTempReq = {.mStartInterval=0, .mEndInterval = rand() % 100000};
            lId++;
            AddToInputBuffer(lTempReq);
            usleep(100);
        }

        int lResponse = GetFromOutBuffer();
    }

    for(int i=0; i<NR_OF_THREADS; ++i)
    {
        pthread_join(lArrayOfThreads[i], NULL);
    }
}
