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

#define NR_OF_THREADS       20
#define MAX_NR_OF_ENTRIES   1024

typedef struct Request
{
    int mId;
    int mStartInterval;
    int mEndInterval;
}Request_t;

typedef struct Response
{
    int mSum;
    int mId;
} Response_t;

typedef struct InBuffer
{
    Request_t mBuffer[MAX_NR_OF_ENTRIES];
    pthread_mutex_t mMutex;
    int mFirstFreePos;
    int mNrOfEntries;
}InBuffer_t;

typedef struct OutBuffer
{
    Response_t mBuffer[MAX_NR_OF_ENTRIES];
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

int Sum(int aStart, int aEnd)
{
    int lSum=0;
    for(unsigned long i=aStart; i < aEnd; ++i)
    {
        unsigned long lIsPrimeNumber = 1;
        //Search for a divider
        for(unsigned long d=2; d<i/2; ++d)
        {
            if(i % d == 0)
            {
                lIsPrimeNumber = 0;    
                break;
            }
        }

        if(lIsPrimeNumber == 1)
        {
            lSum += i;
        }
    }
    return lSum;
}


void AddToOutpBuffer(Response_t aResp)
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

Response_t GetFromOutBuffer()
{
    Response_t lResp;

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
        Response_t lResp = {.mSum = Sum(lReq.mStartInterval, lReq.mEndInterval), .mId = 0};
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
        Request_t lTempReq = {.mStartInterval=1, .mEndInterval = rand() % 10000, .mId = lId};
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
            Request_t lTempReq = {.mStartInterval=1, .mEndInterval = rand() % 10000, .mId = lId};
            lId++;
            AddToInputBuffer(lTempReq);
            usleep(100);
        }

        Response_t lResponse = GetFromOutBuffer();
        printf("Result = %d\n", lResponse.mSum);

    }

    for(int i=0; i<NR_OF_THREADS; ++i)
    {
        pthread_join(lArrayOfThreads[i], NULL);
    }
}
