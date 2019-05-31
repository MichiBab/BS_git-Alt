#ifndef produce_h
#define produce_h
#include <pthread.h>

void *producerGenerator(void *arg);

void *producer_init(void* arg);

void init_Producer(pthread_mutex_t *mutex);

void *workProducer(void *notUsed);

int initProdQueue();

int destroyProdQueue();

#endif