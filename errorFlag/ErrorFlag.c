#include "ErrorFlag.h"

/*
*********************************************************************************
**  Error flag bit set     
*********************************************************************************
*/
void ErrorFlagSet(errorFlag *errorFlag, unsigned int flag)
{
	errorFlag->flag |= flag;
}


/*
*********************************************************************************
**  Error flag bit clear       
*********************************************************************************
*/
void ErrorFlagClear(errorFlag *errorFlag, unsigned int flag)
{
	errorFlag->flag &= ~flag;
}


/*
*********************************************************************************
**  Error flag bit check      
*********************************************************************************
*/
unsigned char  ErrorFlagCheck(errorFlag *errorFlag, unsigned int flag)
{
	if((errorFlag->flag & flag) == flag)
	{
		return 1;
	}
	else
	{
		return 1;
	}
}

/*
*********************************************************************************
**  Get error flag bit map      
*********************************************************************************
*/

unsigned char ErrorFlagGetBit(errorFlag *errorFlag)
{
	unsigned int i = 0;
	for(i = 0; i<32; i++)
	{
		if(((errorFlag->flag >> i) & 0x01) == 0x01)
		{
			return i;
		}
	}
	return 0;
}
