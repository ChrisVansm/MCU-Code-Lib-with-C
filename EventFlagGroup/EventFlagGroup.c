#include "EventFlagGroup.h"

void EventFlagGroupSet(eventFlagGroup *flagGroup, unsigned int bit)
{
	flagGroup->flag |= bit;
}

void EventFlagGroupClear(eventFlagGroup *flagGroup, unsigned int bit)
{
	flagGroup->flag &= ~bit;
}


unsigned char EventFlagGroupCheck(eventFlagGroup *flagGroup, unsigned int bit)
{
	if((flagGroup->flag & bit) == bit)    // If the event flag group is ready, return 1,else return 0
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

