#ifndef err_h
#define err_h

#define FATAL_ERROR 100
#define NO_ERROR 0
int err(int ERROR_NUMBER, char* ErrorMessage, int fatal);
extern int errno;
#endif