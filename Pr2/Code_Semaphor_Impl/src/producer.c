#include "produce.h"
#include "main.h"
#include "fifo.h"
#define SLEEP_PRODUCER 3
    
void init_producer(pthread_mutex_t *mutex){
    pthread_mutex_lock(mutex);
    pthread_mutex_unlock(mutex);
    }

void *producer_init(void* arg){
    struct threadArg *t = (struct threadArg*) arg;
    init_producer(&t->mutex);
    while(true){
        //blockedMechanismus
        sleep(SLEEP_PRODUCER);
        pthread_mutex_lock(&t->mutex);
        pthread_mutex_unlock(&t->mutex);
        pthread_testcancel();
        t->function(NULL);
    }
    return NULL;
    }

