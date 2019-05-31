#ifndef fifo_h
#define fifo_h


int produce(char c);
int consume();
int initFifo();
int mutexDestroyFifo();
int setConditionVarMode();
#endif