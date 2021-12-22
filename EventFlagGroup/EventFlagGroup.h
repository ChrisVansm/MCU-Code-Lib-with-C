#ifndef _EVENT_FLAG_GROUP_H_
#define _EVENT_FLAG_GROUP_H_

typedef struct _eventFlagGroup
{
	unsigned int flag;
}eventFlagGroup;

// Set event flag group
extern void EventFlagGroupSet(eventFlagGroup *flag, unsigned int bit);
// Clear event flag group 
extern void EventFlagGroupClear(eventFlagGroup *flag, unsigned int bit);
// Check bit if ready of event flag group
extern unsigned char EventFlagGroupCheck(eventFlagGroup *flag, unsigned int bit);

#endif
