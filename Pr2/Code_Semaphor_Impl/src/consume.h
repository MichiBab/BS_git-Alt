#ifndef consume_h
#define consume_h
void init_consumer();
void *consumer_init(void *not_used);
int lockConsumer();
int unlockConsumer();
int mutexDestroyConsumer();
#endif