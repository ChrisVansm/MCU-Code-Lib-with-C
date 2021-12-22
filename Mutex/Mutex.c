#include "Mutex.h"


//------------- Get the peripheral mutex
unsigned char MutexGet(MUTEX *mutex)
{
	if(mutex->states)
	{
		mutex->states = MUTEX_BUSY;
		return MUTEX_IDLE;
	}
	else
	{
		return MUTEX_BUSY;
	}
}

//------------- Release the pripheral mutex
void MutexRelease(MUTEX *mutex)
{
	mutex->states = MUTEX_IDLE;
}

//------------- Check the mutex
unsigned char MutexCheck(MUTEX *mutex)
{
	return mutex->states;
}






