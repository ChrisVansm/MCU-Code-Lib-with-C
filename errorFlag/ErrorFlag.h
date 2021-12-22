#ifndef _ERROR_FLAG_H_

/*
*********************************************************************************
**  Variable      
*********************************************************************************
*/

typedef struct _errorFlag
{
	unsigned int flag;
}errorFlag;


/*
*********************************************************************************
**  Functions   
*********************************************************************************
*/

//-------------------------- Error flag set
extern void ErrorFlagSet(errorFlag *errorFlag, unsigned int flag);
//-------------------------- Error flag clear
extern void ErrorFlagClear(errorFlag *errorFlag, unsigned int flag);
//-------------------------- Error flag check
extern unsigned char ErrorFlagCheck(errorFlag *errorFlag, unsigned int flag);
//-------------------------- Error flag get bit number 
extern unsigned char ErrorFlagGetBit(errorFlag *errorFlag);
	
#endif
