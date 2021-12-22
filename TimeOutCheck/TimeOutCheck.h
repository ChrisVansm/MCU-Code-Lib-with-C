#ifndef _TIME_OUT_CHECK_H_
#define _TIME_OUT_CHECK_H_

#define TIME_OUT_TURE      1
#define TIME_OUT_FALSE     0

extern unsigned int timeOutCheckCounter;     // Put this variable into some timer interrupt handler with 1ms interrupt.

extern unsigned char TimeOutCheckMs(unsigned int *counter, unsigned int howlong);  
extern void TimeOutCheckClear(unsigned int *counter);

#endif
