#include "main.h"
#include "produce.h"
#include "control.h"
#include "consume.h"
#include "fifo.h"
#include "taskqueue.h"
#include "consume.h"
#include "ThreadArgs.h"

/**
 * @brief Dieses Programm fuert die Initialisierungen durch und erzeugt alle weiteren Threads des Systems.
 *        Anschließend geht es in den Blocked Zustanad und wartet, bis die von ihm erzeugten Threads 
 *        terminiert sind. Anschließend wird das Programm beendet.
 * @return End of Program
 */
 //TODO in main: ADD GENERATOR PRODUCER/CONSUMER, ADD THREADPOOL CREATION x2, ADD TASKQUEUE INIT x2
//DECLARE

pthread_t controller;
static int init_all(); 
static int wait_till_finished();
struct threadArg prodArg;
struct threadArg prod2Arg;
struct threadArg consArg;
struct threadArg prodGenArg;
struct threadArg consGenArg;
pthread_t prodWorker[WORKER_THREADS_NUM];
pthread_t conWorker[WORKER_THREADS_NUM];
struct threadArg *threadListe[THREADS_NUM];
static int threadArgInit(struct threadArg *threadData, int BEZEICHNER, int sleepTime, void* function);
//END DECLARE
 
int main(int argc, char **argv)
{
    init_all();
    wait_till_finished();
    printf("\n------------\nmain ist fertig\n-------------\n");
	return 0;
}

//Hier koennen Threads erstellt und hinzugefuegt werden. Es muss THREADS_NUM eingestellt werden
// sowie beachtet werden, das jeder Thread einen eigenen Struct hat
static int init_all(){
    
    initFifo();    
    printf("fertig mit init fifo\n");
    initProdQueue();
    initConsQueue();
    //INIT DER ARGUMENTE DER THREADS:
    threadArgInit(&consArg,CONSUMER,SLEEPCONSUMER, &consumerfunction);

    threadArgInit(&prodArg,PRODUCER_1,SLEEPPRODUCER, &producerKlein);

    threadArgInit(&prod2Arg,PRODUCER_2,SLEEPPRODUCER, &producerGross);

    threadArgInit(&prodGenArg,PRODGEN,SLEEPPRODGEN, &producerGenerator);
    
    threadArgInit(&consGenArg,CONSGEN,SLEEPCONSGEN, &consumerGenerator);
    
    //CREATE SECTION: //Controller wird seperat gestartet
    pthread_create(&controller, NULL, control_init, NULL);
    err(errno, "fehler bei CreateController\n",true);

    errno = pthread_create((pthread_t*)&prodArg.thread, NULL, producer_init, (void*)&prodArg);
    err(errno, "fehler bei CreateProducer\n",true);
    
    errno = pthread_create((pthread_t*)&prod2Arg.thread, NULL, producer_init, (void*)&prod2Arg);
    err(errno, "fehler bei mCreateProducer2\n",true);
    
    errno = pthread_create((pthread_t*)&consArg.thread, NULL, consumer_init, (void*)&consArg);  
    err(errno, "fehler bei CreateConsumer\n",true);
    
    
    //GENERATOR INIT:
    errno = pthread_create((pthread_t*)&prodGenArg.thread, NULL, producerGenerator, (void*)&prodGenArg);  
    err(errno, "fehler bei CreateProducerGenerator\n",true);
    
    for(int i = 0; i < WORKER_THREADS_NUM; i++){
        if(pthread_create(&prodWorker[i], NULL, workProducer, NULL) != 0){
            printf("ERROR CREATE PRODWORKER\n");
        }
    }
    
    errno = pthread_create((pthread_t*)&consGenArg.thread, NULL, consumerGenerator, (void*)&consGenArg);  
    err(errno, "fehler bei CreateProducerGenerator\n",true);
    
    for(int i = 0; i < WORKER_THREADS_NUM; i++){
        if(pthread_create(&conWorker[i], NULL, workConsumer, NULL) != 0 ){
            printf("ERROR CREATE CONWORKER\n");
            }
        }
    
    return 0;
    }

static int wait_till_finished(){

    pthread_join(controller, 0);
    return 0;
    }
    
    
int cancelAll(){
    for(int i = 0; i < WORKER_THREADS_NUM; i++){
        if(pthread_cancel(prodWorker[i])){
            printf("Error in WorkerthreadProd cancel\n");
            };
    }
    for(int i = 0; i < WORKER_THREADS_NUM; i++){
        if(pthread_cancel(conWorker[i])){
            printf("Error in WorkerthreadCons cancel\n");
            };
    }
    for(int i = 0; i<THREADS_NUM;i++){
            pthread_cancel(*threadListe[i]->thread);
        }
    return 0;
    }

int terminate(){
    destroyConsQueue();
    destroyProdQueue();
    
    printf("join beginnt\n");
    //WAIT FOR JOIN
    pthread_join(*consArg.thread, 0);
    pthread_join(*prodArg.thread, 0);
    pthread_join(*prod2Arg.thread, 0);
    //Hiernach sind die threads gecanceled, => die mutex können destroyed werden
    printf("init destroy:\n");
    for(int i = 0; i < THREADS_NUM; i++){
        errno = pthread_mutex_destroy(&threadListe[i]->mutex);
        err(errno, "fehler bei MutexDestroy ALL in terminate",false);
        }
    printf("destroy Fifo\n");
    mutexDestroyFifo();
    printf("fertig destroy\n");
    printf("try to cancel controller\n");
    pthread_cancel(controller);
    return 0;
    }

int lockall(){
    for(int i = 0; i<THREADS_NUM;i++){
        lockThread(i);
        }
    return 0;
    }

int lockThread(int THREAD){
    //printf("locked thread number %d\n", THREAD);
    lockUnlockMutex(LOCK,&threadListe[THREAD]->mutex);
    return 0;
    }
    
int unlockThread(int THREAD){
    //printf("unlocked thread number %d\n", THREAD);
    lockUnlockMutex(UNLOCK,&threadListe[THREAD]->mutex);
    return 0;
    }

static int threadArgInit(struct threadArg *threadData, int BEZEICHNER, int sleepTime, void* function){
    threadData->sleepTime = 2;
    threadData->function = function;
    errno = pthread_mutex_init(&threadData->mutex,NULL);
    err(errno, "fehler bei Create Mutex in threadArgInit\n",true);
    threadListe[BEZEICHNER] = threadData;
    return 0;
    }
