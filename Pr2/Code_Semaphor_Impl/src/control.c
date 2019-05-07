#include "main.h"
#include "consume.h"
#include "fifo.h"
#include "produce.h"
static int changeStatus(int THREAD);
int threadStatus[THREADS_NUM];

void *control_init(void *not_used){
    //erste struct ist die des consumers, rest der producer
    lockall();
    //fille den status als locked
    for(int i = 0; i<THREADS_NUM;i++){
            threadStatus[i] = LOCK;
        }
    printf("schreibe jetzt V oder v für Conditional Var Mode, Enter um fortzufahren\n");
    char c;
    c = getchar();
    if(c == 'v' || c == 'V'){
        printf("conditionVariable mode gesetzt\n");
        setConditionVarMode();
        }
    printf("Druecken sie h fuer info\n");
    while(true){
        pthread_testcancel();
        c = getchar();
        if(c=='c' || c=='C'){
            //consumer
            changeStatus(CONSUMER);
            }
        if(c=='1'){
            //producer
            changeStatus(PRODUCER_1);
            }
        if(c=='2'){
            //producer
            changeStatus(PRODUCER_2);
            }
        if(c=='h'){
            //info
            printf("c/C : starte/stoppe Consumer\ng/G : starte/stoppe ConsumerGENERATOR \n1 : Starte/Stoppe producer1\n");
            printf("2 : starte/stoppe producer2\np/P : Starte/Stoppe producerGENERATOR\n");
            printf("q/Q : terminiere das System\nh : liste Moeglichkeiten erneut aus\n");
            }
        if(c=='q' || c=='Q'){
            //unlockt die threads damit cancel clean laeuft und Mutex Destroy fehlerfrei wird
            for(int i = 0; i < THREADS_NUM; i++){
                if(threadStatus[i] == LOCK){
                    unlockThread(i);
                    }
                }
            terminate();
            }
        }
    }

int lockUnlockMutex(int MODUS, pthread_mutex_t *mutex){
    
    if(MODUS == LOCK){
        pthread_mutex_lock(mutex);
    }
    else if(MODUS == UNLOCK){
        pthread_mutex_unlock(mutex);
        }
    else{
        return -1; //ERR
        }
    return 0;
    }

static int changeStatus(int THREAD){
    if(threadStatus[THREAD] == LOCK){
                unlockThread(THREAD);
                threadStatus[THREAD] = UNLOCK;
                }
            else{
                lockThread(THREAD);
                threadStatus[THREAD] = LOCK;
                }
    return 0;
    }