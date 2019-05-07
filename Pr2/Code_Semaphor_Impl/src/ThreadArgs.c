#include "main.h"
#include "ThreadArgs.h"
#include "fifo.h"

char klein = 'a';
char gross = 'A';

void* producerKlein(void* not_used){

    produce(klein);
    if(klein=='z'){ klein = 'a';}
    else{
        klein++;
        }
    return 0;
    }
    
void* producerGross(void* not_used){

    produce(gross);
    if(gross=='Z'){ gross = 'A';}
    else{
        gross++;
        }
    return 0;
    }