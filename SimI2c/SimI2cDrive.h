#ifndef _SIMI2C_H_
#define _SIMI2C_H_
#include "BSP.h"

typedef enum _I2cState
{
	NOACK = 0x44,
	ACK
}I2cState;

extern void SimI2cInit(void);
extern void SimI2cStart(void);
extern void SimI2cRestart(void);
extern void SimI2cStop(void);
extern I2cState SimI2cSendAddr(uint8 addr, uint8 rwflag);
extern void SimI2cRead(uint8 *buff, I2cState ack);
extern I2cState SimI2cWritePtr(uint8 *buff);
extern I2cState SimI2cWriteByte(uint8 data);
extern void IIC_Delay(void);

#endif
