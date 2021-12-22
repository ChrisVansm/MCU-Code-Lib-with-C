/*
**#############################################################################
**      SVN Information
**
**      Checked In          : 2017-3-3
**
**      Revision            : 0.01
**
**      Release Information : Simulation SPI drive
**   
**#############################################################################
*/

#include "SimSpiDrive.h"

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
static void SimSpiDataHigh(void);
static void SimSpiDataLow(void);
static void Delay(uint32 howlong);


/*
**#############################################################################
** Simulation initialization
**#############################################################################
*/
void SimSpiInit(void)
{
	GPIO_PLUTUS_MOSI_ENABLE();
	GPIO_PLUTUS_SCK_ENABLE();
	GPIO_PLUTUS_CS_ENABLE();
	GPIO_PLUTUS_MOSI_SET_LOW();
	GPIO_PLUTUS_SCK_SET_LOW();
	GPIO_PLUTUS_CS_SET_HIGH();   // Set the cs pin to high level
}


/*
**#############################################################################
** Simulation SPI transmit the data
**#############################################################################
*/
void SimSpiTransmit(uint8 *data, uint32 length)
{
	uint32 i = 0;
	uint8 j = 0;
	for(i = 0; i<length; i++)
	{
		for(j = 0; j<8; j++)
		{
			if((*data & 0x80) == 0x80)
			{
				SimSpiDataHigh();
			}
			else
			{
				SimSpiDataLow();
			}
			*data <<= 1;
		}
		data ++;
	}
}


/*
**#############################################################################
** Simulation SPI transmit the data
**#############################################################################
*/
void SimSpiSendByte(uint8 data)
{
	uint8 i = 0;
	for(i = 0; i<8; i++)
	{
		if((data & 0x80) == 0x80)
		{
			SimSpiDataHigh();
		}
		else
		{
			SimSpiDataLow();
		}
		data <<= 1;
	}
}


/*
**#############################################################################
** Simulation SPI produce a high bit
**#############################################################################
*/
static void SimSpiDataHigh(void)
{
	GPIO_PLUTUS_MOSI_SET_HIGH();
	GPIO_PLUTUS_SCK_SET_HIGH();
	GPIO_PLUTUS_SCK_SET_LOW();
	GPIO_PLUTUS_MOSI_SET_LOW();
}


/*
**#############################################################################
** Simulation SPI produce a low bit
**#############################################################################
*/
static void SimSpiDataLow(void)
{
	GPIO_PLUTUS_MOSI_SET_LOW();
	GPIO_PLUTUS_SCK_SET_HIGH();
	GPIO_PLUTUS_SCK_SET_LOW();
}



/*
**#############################################################################
** Produce a clock Signal
**#############################################################################
*/
void SimSpiOneClock(void)
{
	GPIO_PLUTUS_SCK_SET_HIGH();
	GPIO_PLUTUS_SCK_SET_LOW();
}



/*
**#############################################################################
** Produce a Cs Signal
**#############################################################################
*/
void SimSpiOneCs(void)
{
	GPIO_PLUTUS_CS_SET_LOW();
	GPIO_PLUTUS_CS_SET_HIGH();
	GPIO_PLUTUS_CS_SET_LOW();
}
	

/*
**#############################################################################
** Introduce a bit of SW delay
**#############################################################################
*/
static void Delay(uint32 howlong)
{
	int delay;
	if (!howlong) howlong=1;
	for (;howlong!=0;--howlong) 
	{
		for (delay=0;delay<16;delay++);
	}
}
