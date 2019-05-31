#include "consume.h"
#include "main.h"
#include "fifo.h"
#include "taskqueue.h"
#define Sleep_time_Consumer 2
#define CONSUMER_QUEUE "/consumerQueue"
mqd_t consumerQueue;

int initConsQueue(){
    consumerQueue = createTaskQueue(CONSUMER_QUEUE, QUEUE_SIZE);
    return 0;
    }

int destroyConsQueue(){
    destroyTaskQueue(CONSUMER_QUEUE);
    return 0;
    }

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
        t->function(NULL);
        //consume();
        }
    return NULL;
    }

void *consumerGenerator(void *arg){
    struct threadArg *t = (struct threadArg*) arg;
    init_consumer(&t->mutex);
    struct task consumerTask = {(void*) &consumerfunction, NULL};
    while(true){
        pthread_mutex_lock(&t->mutex);
        pthread_mutex_unlock(&t->mutex);
        pthread_testcancel();
        int isFull = sendToTaskQueue(consumerQueue, consumerTask, TASK_PRIORITY,false);
        if(isFull < 0){
            printf("error while inserting task into consumer task queue");
            }
        sleep(t->sleepTime);
    }
    return 0;
}

void *workConsumer(void *notUsed){
    struct task terminateTask = {NULL,NULL};
    struct task taskToExecute = {NULL,NULL};
    bool terminate = false;
    while(!terminate){
        taskToExecute = receiveFromTaskQueue(consumerQueue);
        if(taskToExecute.routineForTask == terminateTask.routineForTask){
            terminate = true;
        }else{
            taskToExecute.routineForTask(taskToExecute.arg);
        }   
    }
    return 0;
}