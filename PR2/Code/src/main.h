#ifndef main_h
#define main_h
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "err.h" 
#include "ThreadArgs.h"
#include <mqueue.h>
#define TASK_PRIORITY 1
#define true 1
#define CONSUMER 0
#define PRODUCER_1 1
#define PRODUCER_2 2
#define PRODGEN 3
#define CONSGEN 4
#define LOCK 0
#define UNLOCK 1
#define THREADS_NUM 5 //4 ohne cons gen zum testen
#define WORKER_THREADS_NUM 5
#define SLEEPPRODUCER 3
#define SLEEPCONSUMER 2
#define SLEEPPRODGEN 1
#define SLEEPCONSGEN 1
#define THREADPOOL_MODE 1
#define QUEUE_SIZE 5


struct threadArg{
    pthread_t *thread;
    pthread_mutex_t mutex;
    void*(*function)(void*); ;//functionpointer 
    int sleepTime;
    };
    
int cancelAll();
int lockThread(int THREAD);
int unlockThread(int THREAD);
int lockall();
int terminate();
#endif