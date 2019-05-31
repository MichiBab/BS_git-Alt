#ifndef control_h
#define control_h

void *control_init(void *not_used);

int lockUnlockMutex(int MODUS, pthread_mutex_t *mutex);
#endif