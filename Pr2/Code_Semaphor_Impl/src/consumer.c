#include "consume.h"
#include "main.h"
#include "fifo.h"
pthread_mutex_t consumeMutex = PTHREAD_MUTEX_INITIALIZER;

int mutexDestroyConsumer(){
    
    pthread_mutex_destroy(&consumeMutex);
    return 0;
    }

void init_consumer(){
    pthread_mutex_lock(&consumeMutex);
    pthread_mutex_unlock(&consumeMutex);
    }

void *consumer_init(void *not_used){
    init_consumer();
    
    while(true){
        //blockedMechanismus
        sleep(2);
        pthread_mutex_lock(&consumeMutex);
        pthread_mutex_unlock(&consumeMutex);
        consume();
        }
    
    return NULL;
    }

//FOR EXTERN USE
int lockConsumer(){
    pthread_mutex_lock(&consumeMutex);
    return 0;
    }
    
int unlockConsumer(){
    pthread_mutex_unlock(&consumeMutex);
    return 0;
    }