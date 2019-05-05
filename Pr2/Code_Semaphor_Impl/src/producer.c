#include "produce.h"
#include "main.h"
#include "fifo.h"
pthread_mutex_t p1mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t p2mutex = PTHREAD_MUTEX_INITIALIZER;

int mutexDestroyProduce(){
    pthread_mutex_destroy(&p1mutex);
    pthread_mutex_destroy(&p2mutex);
    return 0;
    }

void init_producer1(){
    pthread_mutex_lock(&p1mutex);
    pthread_mutex_unlock(&p1mutex);
    }
    
void init_producer2(){
    pthread_mutex_lock(&p2mutex);
    pthread_mutex_unlock(&p2mutex);
    }

void *producer1_init(void *not_used){
    init_producer1();
    char c = 'a';
    while(true){
        //blockedMechanismus
        sleep(3);
        pthread_mutex_lock(&p1mutex);
        pthread_mutex_unlock(&p1mutex);
        
        produce(c);
        printf("-pt1 produziert: %c \n",c);
        if(c == 'z'){
            c = 'a';
        }
        else c+=1;
    }
    return NULL;
    }
    
void *producer2_init(void *not_used){
    init_producer2();
    char c = 'A';
    while(true){
        //blockedMechanismus
        sleep(3);
        pthread_mutex_lock(&p2mutex);
        pthread_mutex_unlock(&p2mutex);
        
        
        produce(c);
        printf("-pt2 produziert: %c \n",c);
        if(c == 'Z'){
            c = 'A';
        }
        else c+=1;
    }
    return NULL;
    }
    
int lockP1(){
    pthread_mutex_lock(&p1mutex);
    return 0;
    }
    
int lockP2(){
    pthread_mutex_lock(&p2mutex);
    return 0;
    }
    
int unlockP1(){
    pthread_mutex_unlock(&p1mutex);
    return 0;
    }
    
int unlockP2(){
    pthread_mutex_unlock(&p2mutex);
    return 0;
    }

