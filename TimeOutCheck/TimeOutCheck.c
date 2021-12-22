#include "TimeOutCheck.h"

unsigned int timeOutCheckCounter = 0;


unsigned char TimeOutCheckMs(unsigned int *counter, unsigned int howlong)
{
	if(*counter == 0)
	{
		*counter = timeOutCheckCounter;
		return TIME_OUT_FALSE;
	}
	else
	{
		if((timeOutCheckCounter - *counter) >= howlong)
		{
			*counter = 0;
			return TIME_OUT_TURE;
		}
		else
		{
			return TIME_OUT_FALSE;
		}
	}
}


void TimeOutCheckClear(unsigned int *counter)
{
	*counter = 0;
}








