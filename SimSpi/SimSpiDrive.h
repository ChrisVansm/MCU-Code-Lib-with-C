#ifndef _SIMSPIDRIVE_H_
#define _SIMSPIDRIVE_H_

#include "BSP.h"


extern void SimSpiInit(void);
extern void SimSpiTransmit(uint8 *data, uint32 length);
extern void SimSpiSendByte(uint8 data);
extern void SimSpiOneClock(void);
extern void SimSpiOneCs(void);

#endif
