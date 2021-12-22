
/*
**#############################################################################
**      SVN Information
**
**      Checked In          : 2016-12-07
**
**      Revision            : 0.01
**
**      Release Information : Plutus02 CRC计算程序
**   
**#############################################################################
*/
#include "Crc.h"



/*
**#############################################################################
** Variable declaration
**#############################################################################
*/
uint16	swCrcResult,
				hwCrcResult;
uint32	crcHighBit,
				crcXor,
				crcMask,
				crcOrder;

/*
**#############################################################################
** Functions
**#############################################################################
*/
uint32 BitReflect (uint32 crc, int bitnum);
uint16 CrcBitByBitFast(uint8 dat);


/*
**#############################################################################
** CRC  initialization
**#############################################################################
*/
void CrcInit(void)
{
	crcHighBit		= 0x8000;				//B15 is the high bit
	crcXor			= 0;
	crcMask			= 0xffff;
	crcOrder		= 16;
	
	swCrcResult = CRCSEED0;
}


/*
**#############################################################################
** CRC reset
**#############################################################################
*/
void CrcReset(void)
{
	swCrcResult = CRCSEED0;
}

/*
**#############################################################################
** CRC校验函数
**#############################################################################
*/
uint16 CrcBitByBitFast(uint8 dat)
{
	// fast bit by bit algorithm without augmented zero bytes.
	// does not use lookup table, suited for CRCPOLY orders between 1...32.

	uint32 j = 0, c, bit = 0;
	uint32 crc = swCrcResult;

	c = dat;
	if (CRCCON_DINBR0) c = BitReflect(c, 8);

	for (j=0x80; j; j>>=1) {
		bit = crc & crcHighBit;
		crc<<= 1;
		if (c & j) bit^= crcHighBit;
		if (bit) crc^= CRCPOLY0;
	}

	if (CRCCON_CRCBR0) crc=BitReflect(crc, crcOrder);
	crc^= crcXor;
	crc&= crcMask;

	swCrcResult = crc;
	
	return(crc);
}

/*
**#############################################################################
** Bit BitReflect
**#############################################################################
*/
uint32 BitReflect (uint32 crc, int bitnum)
{

	// reflects the lower 'bitnum' bits of 'crc'

	uint32 i, j=1, crcout=0;

	for (i=(uint32)1<<(bitnum-1); i; i>>=1) {
		if (crc & i) crcout|=j;
		j<<= 1;
	}
	return (crcout);
}













