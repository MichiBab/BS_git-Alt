#include "main.h"
#include "produce.h"
#include "control.h"
#include "consume.h"
#include "fifo.h"

/**
 * @brief Dieses Programm fuert die Initialisierungen durch und erzeugt alle weiteren Threads des Systems.
 *        Anschließend geht es in den Blocked Zustanad und wartet, bis die von ihm erzeugten Threads 
 *        terminiert sind. Anschließend wird das Programm beendet.
 * @return End of Program
 */
 
//DECLARE
pthread_t produce1;
pthread_t produce2;
pthread_t consumer;
pthread_t controller;
static int init_all(); 
static int wait_till_finished();
//END DECLARE

 
int main(int argc, char **argv)
{
    init_all();
    wait_till_finished();
    printf("\nmain ist fertig\n");
	return 0;
}


static int init_all(){
    initFifo();
    init_consumer();
    
    printf("fertig mit init fifo\n");
    pthread_create(&controller, NULL, control_init, NULL);
    for(int i = 0; i<10;i++){}//Polling to make controller lock down all
    pthread_create(&produce1, NULL, producer1_init, NULL);
    pthread_create(&produce2, NULL, producer2_init, NULL);
    pthread_create(&consumer, NULL, consumer_init, NULL);  
    
    return 0;
    }

static int wait_till_finished(){
    pthread_join(controller, 0);
    return 0;
    }
    
int terminate(){
    int a,b,c = true;
    printf("init terminate:\n");
    do{
        if (a != 0){a = pthread_cancel(consumer);}
        if (b != 0){b = pthread_cancel(produce1);}
        if (c != 0){c = pthread_cancel(produce2);}
    }while(a != 0 || b != 0 || c != 0) ;
    sleep(1);
    //Hiernach sind die threads gecanceled, => die mutex können destroyed werden
    printf("init destroy:\n");
    mutexDestroyConsumer();
    mutexDestroyFifo();
    mutexDestroyProduce();
    printf("fertig destroy\n");
    pthread_cancel(controller);
    return 0;
    }
