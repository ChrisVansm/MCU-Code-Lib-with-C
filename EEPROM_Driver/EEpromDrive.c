/*
**#############################################################################
**      SVN Information
**
**      Checked In          : 2017-3-3
**
**      Revision            : 0.01
**
**      Release Information : EEPROM Drive
**   
**#############################################################################
*/
#include "EEpromDrive.h"
#include "BSP.h"
#include "SimI2cDrive.h"
#include "Loop_queue.h"

/*
**#############################################################################
** Variable declaration
**#############################################################################
*/
uint8 eepromWriteAddr[2] = {0,0};    // 当前EEPROM以写入的最大地址
typedef enum _eepromState
{
	EEPROM_READY,
	EEPROM_WAITING0,
	EEPROM_WAITING1,
	EEPROM_WAITING2,
	EEPROM_FINISH,
}eepromState;

/*
**#############################################################################
** Functions
**#############################################################################
*/
static void EepromAddrAdd(void);

/*
**#############################################################################
** EEPROM initialization
**#############################################################################
*/
void EepromInit(void)
{
//	LoopQueueInit(&e2promRxLq);   // 初始化
}


/*
**#############################################################################
** Write the data to EEPROM
**#############################################################################
*/
taskStateType EepromWrite(uint8 *data, uint32 lengh)
{
	uint8 i = 0;
	static uint8 state = EEPROM_READY;
	
	switch(state)
	{
		case EEPROM_READY:
			if(EepromGetWriteAddr(&eepromWriteAddr[0]) == FINISH)
			{
				state = EEPROM_WAITING0;
			}
			else
			{
				return WAITING;
			}
		break;

		case EEPROM_WAITING0:
			SimI2cStart();
			if(SimI2cSendAddr(0xA0, 0) == NOACK)
			{
				SimI2cStop();
				return WAITING;
			}
			if(SimI2cWriteByte(eepromWriteAddr[0]) == NOACK)
			{
				SimI2cStop();
				return WAITING;
			}
			if(SimI2cWriteByte(eepromWriteAddr[1]) == NOACK)
			{
				SimI2cStop();
				return WAITING;
			}
			for(i = 0; i<lengh; i++)
			{
				if(SimI2cWritePtr(data) == NOACK)
				{
					SimI2cStop();
					return WAITING;
				}
				EepromAddrAdd();
				data ++;
			}
			SimI2cStop();
			state = EEPROM_WAITING1;
		break;
			
		case EEPROM_WAITING1:
			SimI2cStart();	
			if(SimI2cSendAddr(0xA0, 0) == NOACK)
			{
				SimI2cStop();
				return WAITING;
			}
			if(SimI2cWriteByte(0) == NOACK)
			{
				SimI2cStop();
				return WAITING;
			}
			if(SimI2cWriteByte(0) == NOACK)
			{
				SimI2cStop();
				return WAITING;
			}
			if(SimI2cWriteByte(eepromWriteAddr[0]) == NOACK)
			{
				SimI2cStop();
				return WAITING;
			}
			if(SimI2cWriteByte(eepromWriteAddr[1]) == NOACK)
			{
				SimI2cStop();
				return WAITING;
			}
			SimI2cStop();
			state = EEPROM_READY;
			return FINISH;
		
		default:
		break;
	}
	return WAITING;
}

/*
**#############################################################################
** Get a data from EEPROM
**#############################################################################
*/
void EepromRead(uint8 *buff, uint8 addrHigh, uint8 addrLow, uint32 lengh)
{

}


/*
**#############################################################################
** Get Write address
**#############################################################################
*/
taskStateType EepromGetWriteAddr(uint8 *addr)
{
	static uint8 state = EEPROM_READY;
	if((state == EEPROM_READY)||(state == EEPROM_WAITING0))
	{
		SimI2cStart();
		if(SimI2cSendAddr(0xA0, 0) == NOACK)
		{
			SimI2cStop();
			return WAITING;
		}
		if(SimI2cWriteByte(0) == NOACK)
		{
			SimI2cStop();
			return WAITING;
		}
		if(SimI2cWriteByte(0) == NOACK)
		{
			SimI2cStop();
			return WAITING;
		}
		SimI2cRestart();
		if(SimI2cSendAddr(0xA0, 1) == NOACK)
		{
			SimI2cStop();
			return WAITING;
		}
		SimI2cRead(addr, NOACK);
		SimI2cStop();
		state = EEPROM_WAITING1;
	}

	addr ++;
	
	if(state == EEPROM_WAITING1)
	{
		SimI2cStart();		
		if(SimI2cSendAddr(0xA0, 0) == NOACK)
		{
			SimI2cStop();
			return WAITING;
		}
		if(SimI2cWriteByte(0) == NOACK)
		{
			SimI2cStop();
			return WAITING;
		}
		if(SimI2cWriteByte(1) == NOACK)
		{
			SimI2cStop();
			return WAITING;
		}
		SimI2cRestart();
		if(SimI2cSendAddr(0xA0, 1) == NOACK)
		{
			SimI2cStop();
			return WAITING;
		}
		SimI2cRead(addr, NOACK);
		SimI2cStop();
		state = EEPROM_READY;
		return FINISH;
	}	
	return WAITING;
}


/*
**#############################################################################
** Clear EEPROM
**#############################################################################
*/
taskStateType EepromClear(void)
{
	static uint8 state = EEPROM_READY;

	if((state == EEPROM_READY)||(state == EEPROM_WAITING0))
	{
		SimI2cStart();
		if(SimI2cSendAddr(0xA0, 0) == NOACK)
		{
			SimI2cStop();
			return WAITING;
		}
		if(SimI2cWriteByte(0) == NOACK)
		{
			SimI2cStop();
			return WAITING;
		}
		if(SimI2cWriteByte(0) == NOACK)
		{
			SimI2cStop();
			return WAITING;
		}
		if(SimI2cWriteByte(0) == NOACK)
		{
			SimI2cStop();
			return WAITING;
		}
		SimI2cStop();
		state = EEPROM_WAITING1;
	}
	
	if(state == EEPROM_WAITING1)
	{
		SimI2cStart();
		if(SimI2cSendAddr(0xA0, 0) == NOACK)
		{
			SimI2cStop();
			return WAITING;
		}
		if(SimI2cWriteByte(0) == NOACK)
		{
			SimI2cStop();
			return WAITING;
		}
		if(SimI2cWriteByte(1) == NOACK)
		{
			SimI2cStop();
			return WAITING;
		}
		if(SimI2cWriteByte(2) == NOACK)
		{
			SimI2cStop();
			return WAITING;
		}
		SimI2cStop();
		state = EEPROM_READY;
		return FINISH;
	}
	return END;
}


/*
**#############################################################################
** Read ALL data from EEPROM
**#############################################################################
*/
taskStateType EepromReadAll(uint8 *buff)
{
	uint32 i = 0;
	static uint8 state = EEPROM_READY;

	switch(state)
	{
		case EEPROM_READY:
			if(EepromGetWriteAddr(&eepromWriteAddr[0]) == FINISH)
			{
				state = EEPROM_WAITING0;
			}
			else
			{
				return WAITING;
			}
		break;
			
		case EEPROM_WAITING0:
			SimI2cStart();
			if(SimI2cSendAddr(0xA0, 1) == NOACK)
			{
				return WAITING;
			}
			else
			{
				state = EEPROM_WAITING1;
			}
		break;
		
		case EEPROM_WAITING1:
			for(i = 2;  i<((eepromWriteAddr[0]*256) + eepromWriteAddr[1]-1); i++)
			{
				SimI2cRead(buff, ACK);
				buff ++;
			}	
			SimI2cRead(buff, NOACK);
			SimI2cStop();
			state = EEPROM_READY;
			return FINISH;
			
		default:
			return WAITING;
	}
	return WAITING;
}

/*
**#############################################################################
** Read ALL data from EEPROM
**#############################################################################
*/
static void EepromAddrAdd(void)
{
	if(eepromWriteAddr[1] == 0xFF)
	{
		eepromWriteAddr[0]++;
		eepromWriteAddr[1] = 0;
	}
	else
	{
		eepromWriteAddr[1] ++;
	}
}

