#include "produce.h"
#include "main.h"
#include "fifo.h"
#include "taskqueue.h"
#define PRODUCER_QUEUE "/producerQueue"
pthread_t prodWorker[WORKER_THREADS_NUM];
mqd_t producerQueue;

int destroyProdQueue(){
    destroyTaskQueue(PRODUCER_QUEUE);
    return 0;
    }

int initProdQueue(){
    producerQueue = createTaskQueue(PRODUCER_QUEUE, QUEUE_SIZE);
    return 0;
    }
    
void init_producer(pthread_mutex_t *mutex){
    pthread_mutex_lock(mutex);
    pthread_mutex_unlock(mutex);
    }

void *producer_init(void* arg){
    struct threadArg *t = (struct threadArg*) arg;
    init_producer(&t->mutex);
    int sleeptime =  t->sleepTime;
    while(true){
        //blockedMechanismus
        sleep(sleeptime);
        pthread_mutex_lock(&t->mutex);
        pthread_mutex_unlock(&t->mutex);
        pthread_testcancel();
        t->function(NULL);
    }
    return NULL;
    }
    
void *workProducer(void *taskqueue){
    struct task terminateTask = {NULL,NULL};
    struct task taskToExecute;
    bool terminate = false;
    while(!terminate){
        taskToExecute = receiveFromTaskQueue(producerQueue);
        if(taskToExecute.routineForTask == terminateTask.routineForTask){
            terminate = true;
        }else{
            taskToExecute.routineForTask(taskToExecute.arg);
        }
    }
    return 0;
}

void *producerGenerator(void *arg){
    struct threadArg *t = (struct threadArg*) arg;
    init_producer(&t->mutex);
    struct task producerTask = {(void*) &producerKlein, NULL}; 
    while(true){
        pthread_mutex_lock(&t->mutex);
        pthread_mutex_unlock(&t->mutex);
        pthread_testcancel();
        int isFull = sendToTaskQueue(producerQueue, producerTask, TASK_PRIORITY,false);
        if(isFull < 0){
            err(1,"error while inserting task into producer task queue",false);
        }
        sleep(t->sleepTime);
        }
	return 0;
    }


