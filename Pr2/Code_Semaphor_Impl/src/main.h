#ifndef main_h
#define main_h
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "err.h" 
#include "ThreadArgs.h"
#define true 1
#define CONSUMER 0
#define PRODUCER_1 1
#define PRODUCER_2 2
#define THREADS_NUM 3
#define LOCK 0
#define UNLOCK 1

struct threadArg{
    pthread_mutex_t mutex;
    void*(*function)(void*); ;//functionpointer 
    };
    
int lockThread(int THREAD);
int unlockThread(int THREAD);
int lockall();
int terminate();
#endif