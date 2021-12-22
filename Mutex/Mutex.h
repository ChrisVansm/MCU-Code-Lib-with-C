#ifndef _MUTEX_H_
#define _MUTEX_H_

#define MUTEX_BUSY     0
#define MUTEX_IDLE     1

typedef struct _mutex
{
	unsigned char states;
}MUTEX;

extern unsigned char MutexGet(MUTEX *mutex);
extern void MutexRelease(MUTEX *mutex);
extern unsigned char MutexCheck(MUTEX *mutex);

#endif
