#ifndef produce_h
#define produce_h
#include <pthread.h>

void *producer_init(void* arg);

void init_Producer(pthread_mutex_t *mutex);


#endif