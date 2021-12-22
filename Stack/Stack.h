/*
**#############################################################################
**      SVN Information
**
**      Checked In          :
**
**      Revision            :
**
**      Release Information :
**#############################################################################
*/

////////////////////////////////////////////////////////////////////////////////
//
// This head file :
//
// Stack head file, supply 8-Bits,32-Bits and void type pointer
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _STACK_H_
#define _STACK_H_

#define STACK_MAX_DEEP   128             // The max deep of stack

typedef enum _StackStates
{
    STACK_FULL,
    STACK_EMPTY,
    STACK_ERROR,
    STACK_FINISH,
}StackStates;

typedef struct _uint8Stack
{
    unsigned char data[STACK_MAX_DEEP];    // Data of stack
    unsigned int top;                      // The top pointer of stack
}uint8Stack;

typedef struct _uint32Stack
{
    unsigned int data[STACK_MAX_DEEP];
    unsigned int top;
}uint32Stack;

typedef struct _voidStack
{
    void * pointer[STACK_MAX_DEEP];
    unsigned int top;    
}voidStack;

//--------------------------------------------------------------------------------------------------------//
//------------Stack initialization with 8-bits
extern void uint8StackInit(uint8Stack *stack);
//------------Stack Clear
extern void uint8StackClear(uint8Stack *stack);
//------------Stack push one data with 8-bits
extern StackStates uint8StackPush(uint8Stack *stack, unsigned char data);
//------------Stack push Multiple data with 8-bits
extern StackStates uint8StackPushMul(uint8Stack *stack, unsigned char *data, unsigned int length);
//------------Stack pop one data with 8-bits
extern StackStates uint8StackPop(uint8Stack *stack, unsigned char *data);
//------------Stack pop Multiple data with 8-bits
extern StackStates uint8StackPopMul(uint8Stack *stack, unsigned char *data, unsigned int length);
//------------Stack get the now deep with 8-bits
extern unsigned int uint8StackGetDeep(uint8Stack *stack);
//--------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------//
//------------Stack initialization with 32-bits
extern void uint32StackInit(uint32Stack *stack);
//------------Stack Clear
extern void voidStackClear(voidStack *stack);
//------------Stack push one data with 32-bits
extern StackStates uint32StackPush(uint32Stack *stack, unsigned int data);
//------------Stack push Multiple data with 32-bits
extern StackStates uint32StackPushMul(uint32Stack *stack, unsigned int *data, unsigned int length);
//------------Stack pop one data with 32-bits
extern StackStates uint32StackPop(uint32Stack *stack, unsigned int *data);
//------------Stack pop Multiple data with 32-bits
extern StackStates uint32StackPopMul(uint32Stack *stack, unsigned int *data, unsigned int length);
//------------Stack get the now deep with 32-bits
extern unsigned int uint32StackGetDeep(uint32Stack *stack);
//--------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------//
//------------Stack initialization with void type pointer
extern void voidStackInit(voidStack *stack);
//------------Stack Clear
extern void voidStackClear(voidStack *stack);
//------------Stack push one pointer with void
extern StackStates voidStackPush(voidStack *stack, void *pointer);
//------------Stack pop one pointer with void
extern StackStates voidStackPop(voidStack *stack, void **pointer);
//------------Stack get the now deep with void
extern unsigned int voidStackGetDeep(voidStack *stack);
//--------------------------------------------------------------------------------------------------------//

#endif





