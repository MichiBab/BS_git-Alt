#ifndef produce_h
#define produce_h

void *producer1_init(void *not_used);

void *producer2_init(void *not_used);

int lockP1();
int lockP2();
int unlockP2();
int unlockP1();
void init_Producer1();
void init_Producer2();
int mutexDestroyProduce();
#endif