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
static int produceCon(char c);
static int consumeCon();
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
static int count = 0;
#define false 0
static int conditionVarMode = 0;


int setConditionVarMode(){
    conditionVarMode=1;
    return 0;
    }

int mutexDestroyFifo(){
    errno = sem_destroy(&overflow);
    err(errno, "fehler bei mutexDestroyFifo\n",false);
    errno = sem_destroy(&underflow);
    err(errno, "fehler bei mutexDestroyFifo\n",false);
    errno = pthread_mutex_destroy(&mutex);
    err(errno, "fehler bei mutexDestroyFifo\n",false);
    errno = pthread_cond_destroy(&full);
    err(errno, "fehler bei mutexDestroyFifo\n",false);
    errno = pthread_cond_destroy(&empty);
    return 0;
    }

//Init
int initFifo(){
    errno = sem_init(&overflow, 0, fifo_max); 
    err(errno, "fehler bei Sem_InitFifo\n",true);
    errno = sem_init(&underflow, 0, 0);
    err(errno, "fehler bei mutexDestroyFifo\n",true);
    fifo = (char*) malloc(FIFO_SIZE * sizeof(char));
    if(fifo == NULL){
        err(-1,"MallocErrorFifo\n",true);
        }
    indexFifo = 0;
    lastItem = 0; 
    return 0;
    }
    

//Fuegt char in fifo rein. under/overflow durch semaphoren geschützt
int produce(char c){
    if(conditionVarMode){produceCon(c);}
    else{
        sem_wait(&overflow);
        pthread_mutex_lock(&mutex);
         //critical section
        pthread_testcancel();
        fifo[indexFifo] = c;
        printf("Produziert: %c \n", c);
        updateIndex(&indexFifo);
         //end  of critical section
        pthread_mutex_unlock(&mutex);
        sem_post(&underflow);

    }
    return 0;
    }
    
//entfernt char aus fifo gesteuert durch under/overflow und mutex
int consume(){
    if(conditionVarMode){consumeCon();}
    else{
        sem_wait(&underflow);
        pthread_mutex_lock(&mutex);
        //TODO: hier unlock aufruf auf den stack pushen
        pthread_testcancel();
        char x = fifo[lastItem];
        printf("Konsumiert: %c \n", x);    
        updateIndex(&lastItem);
        pthread_mutex_unlock(&mutex);
        sem_post(&overflow);
        
        
    }
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

static int produceCon(char c){
    pthread_mutex_lock(&mutex);
    pthread_testcancel();
    while (count == FIFO_SIZE){                // check if the buffer is fullcond_wait(&empty, &mutex);
        pthread_cond_wait(&empty, &mutex); 
        }
    fifo[indexFifo] = c;
    printf("Produziert: %c \n",c);
    updateIndex(&indexFifo);
    count++;    // wait for buffer to be emptied
    pthread_cond_signal(&full);
    pthread_mutex_unlock(&mutex);
    return 0;
    }
    
static int consumeCon(){
    pthread_mutex_unlock(&mutex);
    pthread_testcancel();
    while (count == 0){
        pthread_cond_wait(&full, &mutex);
        }
    char x = fifo[lastItem];
    printf("Konsumiert: %c \n", x);
    updateIndex(&lastItem);
    count--;
    pthread_cond_signal(&empty);
    pthread_mutex_unlock(&mutex);
    return 0;
    }