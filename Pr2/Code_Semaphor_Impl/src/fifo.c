#include "fifo.h"
#include "main.h"
#define FIFO_SIZE 10
#define fifo_max 9
static int updateIndex(int *value);
sem_t overflow;
sem_t underflow; 
int overflowWert;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int lastItem;
int indexFifo;
char *fifo;

int mutexDestroyFifo(){
    sem_destroy(&overflow);
    sem_destroy(&underflow);
    pthread_mutex_destroy(&mutex);
    return 0;
    }

//Init
int initFifo(){
    sem_init(&overflow, 0, fifo_max); 
    sem_init(&underflow, 0, 0);
    fifo = (char*) malloc(FIFO_SIZE * sizeof(char));
    indexFifo = 0;
    lastItem = 0; 
    return 0;
    }

//Fuegt char in fifo rein. under/overflow durch semaphoren geschützt
int produce(char c){
    
    sem_wait(&overflow);

    pthread_mutex_lock(&mutex);
     //critical section
    
    fifo[indexFifo] = c;
    updateIndex(&indexFifo);
     //end  of critical section
    pthread_mutex_unlock(&mutex);
    
    sem_post(&underflow);
    
    return 0;
    }
    
//entfernt char aus fifo gesteuert durch under/overflow und mutex
int consume(){
    
    sem_wait(&underflow);
    
    pthread_mutex_lock(&mutex);
    

    char x = fifo[lastItem];    
    printf("Konsumiert: %c \n", x);
    updateIndex(&lastItem);
    

    pthread_mutex_unlock(&mutex);
    
    sem_post(&overflow);
    return 0;
    }
    
//updatet Value Index zyklisch
static int updateIndex(int *value){
    
    if(*value == fifo_max){
        *value = 0;
        }
    else{
        *value +=1;
        }
    return 0;
    }
