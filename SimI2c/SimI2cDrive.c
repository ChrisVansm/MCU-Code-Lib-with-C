/*
**#############################################################################
**      SVN Information
**
**      Checked In          : 2017-3-3
**
**      Revision            : 0.01
**
**      Release Information : Simulation i2c drive
**   
**#############################################################################
*/
#include "SimI2cDrive.h"

/*
**#############################################################################
** Variable declaration
**#############################################################################
*/


/*
**#############################################################################
** Functions
**#############################################################################
*/
static void SimI2cHighBit(void);
static void SimI2cLowBit(void);
static I2cState SimI2cReturnAck(void);

/*
**#############################################################################
** Simulation i2c initialization
**#############################################################################
*/
void SimI2cInit(void)
{
	GPIO_EEPROM_SDA_DISABLE();
	GPIO_EEPROM_SCL_DISABLE();
}


/*
**#############################################################################
** Generate a start bit
**#############################################################################
*/
void SimI2cStart(void)
{
	GPIO_EEPROM_SDA_SET_HIGH();
	GPIO_EEPROM_SCL_SET_HIGH();
	IIC_Delay();
	GPIO_EEPROM_SDA_SET_LOW();
	IIC_Delay();
	GPIO_EEPROM_SCL_SET_LOW();
	IIC_Delay();
}

/*
**#############################################################################
** Generate a restart bit
**#############################################################################
*/
void SimI2cRestart(void)
{
	GPIO_EEPROM_SDA_SET_HIGH();
	GPIO_EEPROM_SCL_SET_HIGH();
	IIC_Delay();
	GPIO_EEPROM_SDA_SET_LOW();
	IIC_Delay();
	GPIO_EEPROM_SCL_SET_LOW();
	IIC_Delay();
}

/*
**#############################################################################
** Generate a stop bit
**#############################################################################
*/
void SimI2cStop(void)
{
	GPIO_EEPROM_SDA_SET_LOW();
	GPIO_EEPROM_SCL_SET_HIGH();
	IIC_Delay();
	GPIO_EEPROM_SDA_SET_HIGH();
	IIC_Delay();
}

/*
**#############################################################################
** Send the address with read-write bit
**#############################################################################
*/
I2cState SimI2cSendAddr(uint8 addr, uint8 rwflag)
{
	uint8 i = 0;
	addr |= rwflag;        // Add read-write bit
	for(i = 0; i<8; i++)
	{
		if((addr&0x80) == 0x80)
		{
			SimI2cHighBit();
		}
		else
		{
			SimI2cLowBit();
		}
		addr <<= 1;
	}
	return SimI2cReturnAck();
}

/*
**#############################################################################
** Read a byte and put it into buff
**#############################################################################
*/
void SimI2cRead(uint8 *buff, I2cState ack)
{
	uint8 i = 0;
	*buff = 0;
	GPIO_EEPROM_SDA_DISABLE();
	for(i = 0; i<8; i++)
	{
		*buff <<= 1;
		GPIO_EEPROM_SCL_SET_HIGH();
		IIC_Delay();
		if(GPIO_EEPROM_SDA_GET())
		{
			GPIO_EEPROM_SCL_SET_LOW();
			*buff |= BIT_0;
			IIC_Delay();
		}
		else
		{
			GPIO_EEPROM_SCL_SET_LOW();
			IIC_Delay();
		}
	}
	if(ack == ACK)
	{
		SimI2cLowBit();
		GPIO_EEPROM_SDA_DISABLE();
	}
	else
	{
		SimI2cHighBit();
	}
}


/*
**#############################################################################
** Write form pointer by simulation i2c
**#############################################################################
*/
I2cState SimI2cWritePtr(uint8 *buff)
{
	uint8 i = 0;
	uint8 tempData;
	tempData = *buff;
	for(i = 0; i<8; i++)
	{
		if((tempData&0x80) == 0x80)
		{
			SimI2cHighBit();
		}
		else
		{
			SimI2cLowBit();
		}
		tempData <<= 1;
	}
	return SimI2cReturnAck();
}

/*
**#############################################################################
** Write data by simulation i2c
**#############################################################################
*/
I2cState SimI2cWriteByte(uint8 data)
{
	uint8 i = 0;
	uint8 tempData;
	tempData = data;
	for(i = 0; i<8; i++)
	{
		if((data&0x80) == 0x80)
		{
			SimI2cHighBit();
		}
		else
		{
			SimI2cLowBit();
		}
		data <<= 1;
	}
	return SimI2cReturnAck();
}


/*
**#############################################################################
** Produce a High bit
**#############################################################################
*/
static void SimI2cHighBit(void)
{
	GPIO_EEPROM_SDA_SET_HIGH();
	GPIO_EEPROM_SCL_SET_HIGH();
	IIC_Delay();
	GPIO_EEPROM_SCL_SET_LOW();
	IIC_Delay();
}

/*
**#############################################################################
** Produce a Low bit
**#############################################################################
*/
static void SimI2cLowBit(void)
{
	GPIO_EEPROM_SDA_SET_LOW();
	GPIO_EEPROM_SCL_SET_HIGH();
	IIC_Delay();
	GPIO_EEPROM_SCL_SET_LOW();
	IIC_Delay();
}

/*
**#############################################################################
** Return ACK
**#############################################################################
*/
static I2cState SimI2cReturnAck(void)
{
	GPIO_EEPROM_SDA_DISABLE();
	GPIO_EEPROM_SCL_SET_HIGH();
	IIC_Delay();
	if(GPIO_EEPROM_SDA_GET())
	{
		GPIO_EEPROM_SCL_SET_LOW();
		IIC_Delay();
		return NOACK;
	}
	else
	{
		GPIO_EEPROM_SCL_SET_LOW();
		IIC_Delay();
		return ACK;
	}
}

/*
**#############################################################################
** I2c delay
**#############################################################################
*/
void IIC_Delay(void)
{
	uint32 i = 0;
	for(i = 0; i<1;i++);
}

