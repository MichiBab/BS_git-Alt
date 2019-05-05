#include "main.h"
#include "consume.h"
#include "produce.h"
int consumerSt=0;
int producer1St=0;
int producer2St=0;
static int lockall();
static int state_p1();
static int state_p2();
static int state_cons();


static int lockall(){
    lockConsumer();
    lockP2();
    lockP1();
    return 0;
    }

void *control_init(void *not_used){
    printf("Programm startet. Druecken sie h fuer info\n");
    lockall();//LOCK THREADS
    while(true){
        char c;
        c = getchar();
        if(c=='c' || c=='C'){
            //consumer
            state_cons();
            }
        if(c=='1'){
            state_p1();
            }
        if(c=='2'){
            //p2
            state_p2();
            }    
        if(c=='h'){
            //info
            printf("c/C : starte/stoppe Consumer\n1 : starte/stoppe Producer1\n2 : starte/stoppe Producer2\n");
            printf("q/Q : terminiere das System\nh : liste Moeglichkeiten erneut aus\n");
            }
        if(c=='q'){
            terminate();
            }
        }
    
    }

static int state_p1(){
    if(producer1St == 0){//means Producer is locked
        producer1St = 1;
        unlockP1();
        }
    else{
        producer1St=0;
        lockP1();
        }
    return 0;
    }
    
    
static int state_p2(){
    if(producer2St == 0){//means Producer is locked
        producer2St = 1;
        unlockP2();
        }
    else{
        producer2St=0;
        lockP2();
        }
    return 0;
    }
    
static int state_cons(){
    if(consumerSt == 0){//means Producer is locked
        consumerSt = 1;
        unlockConsumer();
        }
    else{
        consumerSt=0;
        lockConsumer();
        }
    return 0;
    }
