#ifndef consume_h
#define consume_h
#include <pthread.h>
void init_consumer(pthread_mutex_t *mutex);
void *consumer_init(void *not_used);
#endif