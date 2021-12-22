#ifndef _EEPROMDRIVE_H_
#define _EEPROMDRIVE_H_
#include "App.h"

extern void EepromInit(void);
extern taskStateType EepromWrite(uint8 *data, uint32 lengh);
void EepromRead(uint8 *buff, uint8 addrHigh, uint8 addrLow, uint32 lengh);
extern taskStateType EepromClear(void);
extern taskStateType EepromReadAll(uint8 *buff);
taskStateType EepromGetWriteAddr(uint8 *addr);
	
#endif
