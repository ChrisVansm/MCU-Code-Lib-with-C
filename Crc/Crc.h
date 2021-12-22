#ifndef _CRC_H_
#define _CRC_H_

#define uint16 unsigned short
#define uint32 unsigned int
#define uint8  unsigned char
    
#define NULL    0
#define FALSE   0
#define TRUE    1

#define CRCPOLY0                0x1021
#define CRCCON_DINBR0       0
#define CRCCON_CRCBR0       0
#define CRCSEED0                0x0000

extern uint16       swCrcResult,
                                hwCrcResult;
extern uint32       crcHighBit,
                                crcXor,
                        crcMask,
                        crcOrder;

//---------------- Crc initialization (Be used by plutus communication)
extern void CrcInit(void);

//---------------- Crc reset
extern void CrcReset(void);

//---------------- Crc calculate
extern uint16 CrcBitByBitFast(uint8 dat);

#endif
