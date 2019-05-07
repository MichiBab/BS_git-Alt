#include "main.h"
#include "produce.h"
#include "control.h"
#include "consume.h"
#include "fifo.h"
#include "taskqueue.h"
#include "consume.h"
#include "getcharTimeout.h"
#include "ThreadArgs.h"

/**
 * @brief Dieses Programm fuert die Initialisierungen durch und erzeugt alle weiteren Threads des Systems.
 *        Anschließend geht es in den Blocked Zustanad und wartet, bis die von ihm erzeugten Threads 
 *        terminiert sind. Anschließend wird das Programm beendet.
 * @return End of Program
 */
 
//DECLARE
pthread_t producer;
pthread_t producer2;
pthread_t consumer;
pthread_t controller;
static int init_all(); 
static int wait_till_finished();
struct threadArg prod;
struct threadArg prod2;
struct threadArg cons;
struct threadArg *threadListe[THREADS_NUM];
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
    
    cons.function = NULL;
    errno = pthread_mutex_init(&cons.mutex,NULL);
    err(errno, "fehler bei Create Mutex\n",true);
    threadListe[CONSUMER] = &cons;
    
    prod.function = &producerKlein;
    errno = pthread_mutex_init(&prod.mutex,NULL);
    err(errno, "fehler bei CreateController\n",true);
    threadListe[PRODUCER_1] = &prod;
    
    prod2.function = &producerGross;
    errno = pthread_mutex_init(&prod2.mutex,NULL);
    err(errno, "fehler bei CreateController\n",true);
    threadListe[PRODUCER_2] = &prod2;
    
    pthread_create(&controller, NULL, control_init, NULL);
    err(errno, "fehler bei CreateController\n",true);
    printf("controller created\n");
        
   // sleep(1);//damit controller alle lockt
        
    errno = pthread_create(&producer, NULL, producer_init, (void*)&prod);
    err(errno, "fehler bei CreateProducer\n",true);
    
    errno = pthread_create(&producer2, NULL, producer_init, (void*)&prod2);
    err(errno, "fehler bei mCreateProducer2\n",true);
    
    errno = pthread_create(&consumer, NULL, consumer_init, (void*)&cons);  
    err(errno, "fehler bei CreateConsumer\n",true);
    
    return 0;
    }

static int wait_till_finished(){

    pthread_join(controller, 0);
    return 0;
    }
    
int terminate(){
    pthread_cancel(consumer);

    pthread_cancel(producer);

    pthread_cancel(producer2);
    
    printf("join beginnt\n");
    //WAIT FOR JOIN
    pthread_join(consumer, 0);
    pthread_join(producer, 0);
    pthread_join(producer2, 0);
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
