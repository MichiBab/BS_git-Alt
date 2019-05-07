#include "consume.h"
#include "main.h"
#include "fifo.h"
#define Sleep_time_Consumer 2

void init_consumer(pthread_mutex_t *consumeMutex){
    pthread_mutex_lock(consumeMutex);
    pthread_mutex_unlock(consumeMutex);
    }

void *consumer_init(void *arg){
    struct threadArg *t = (struct threadArg*) arg;
    init_consumer(&t->mutex);
    while(true){
        //blockedMechanismus
        sleep(Sleep_time_Consumer);
        pthread_mutex_lock(&t->mutex);
        pthread_mutex_unlock(&t->mutex);
        pthread_testcancel();
        consume();
        }
    
    return NULL;
    }

