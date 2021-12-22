/*
*******************************************************************************
**      SVN Information
**
**      Checked In          :
**
**      Revision            :
**
**      Release Information :
*******************************************************************************
*/
#include "Stack.h"

/*
*******************************************************************************
**Name : 8bits Stack initializaton
**Input: Stack pointer
**Return: None
*******************************************************************************
*/
void uint8StackInit(uint8Stack *stack)
{
		static unsigned int i = 0;
		stack->top = 0;
		for(i = 0; i<STACK_MAX_DEEP; i++)
		{
			stack->data[i] = 0;
		}
}

/*
*******************************************************************************
**Name : 8bits Stack Clear
**Input: Stack pointer
**Return: None
*******************************************************************************
*/
void uint8StackClear(uint8Stack *stack)
{
		static unsigned int i = 0;
		for(i = 0; i<STACK_MAX_DEEP;i++)
		{
			stack->data[i] = 0;
		}
		stack->top = 0;
}

/*
*******************************************************************************
** Name :  8bits Stack Push data
** Input0: (*stack)Stack pointer
** Input1: (data)One data be pushed int stack
** Return: Stack states
**         (STACK_FINISH): The data has been pushed into stack
**         (STACK_FULL)  : The stack had be STACK_FULL,can't push the data into stack
*******************************************************************************
*/
StackStates uint8StackPush(uint8Stack *stack, unsigned char data)
{
    if(uint8StackGetDeep(stack) >= STACK_MAX_DEEP)   // If stack has been STACK_FULL, return "STACK_FULL"
    {
        return STACK_FULL;
    }
    else
    {    
        stack->data[stack->top] = data;
        stack->top ++;
        return STACK_FINISH;
    }
}

/*
*******************************************************************************
** Name :  8bits Stack Push Multiple data
** Input0: (*stack)Stack pointer
** Input1: (*data)The pointer of data
** Input2: (length)The length of data
** Return: Stack states
**         (STACK_FINISH): The data has been pushed into stack
**         (STACK_FULL)  : The stack had be STACK_FULL,can't push the data into stack
*******************************************************************************
*/
StackStates uint8StackPushMul(uint8Stack *stack, unsigned char *data, unsigned int length)
{
    unsigned int i = 0;
    for(i = 0; i<length; i++)
    {    
        if(uint8StackGetDeep(stack) >= STACK_MAX_DEEP)
        {
            return STACK_FULL;
        }
        else
        {
            stack->data[stack->top] = *data;
            stack->top ++;
        }
        data ++;
    }
    return STACK_FINISH;
}

/*
*******************************************************************************
** Name :   8bits Stack Pop data 
** Input0: (*stack) Stack pointer
** Input1: (*data) The pointer which stack pop the data put into it.
** Return : Stack states
**          (FNISH): The data has been pop from stack,and put into *data.
**          (STACK_EMPTY): The stack is STACK_EMPTY,can't pop data from it.
*******************************************************************************
*/
StackStates uint8StackPop(uint8Stack *stack, unsigned char *data)
{
    if(uint8StackGetDeep(stack) == 0)
    {
        return STACK_EMPTY;
    }
    else
    {
        stack->top --;
        *data = stack->data[stack->top];
        stack->data[stack->top] = 0;
        return STACK_FINISH;
    }
}

/*
*******************************************************************************
** Name :   8bits Stack Pop Multiple data 
** Input0: (*stack) Stack pointer
** Input1: (*data) The pointer of data
** Input2: (length)The length of data be pop
** Return : Stack states
**          (FNISH): The data has been pop from stack,and put into *data.
**          (STACK_EMPTY): The stack is STACK_EMPTY,can't pop data from it.
*******************************************************************************
*/
StackStates uint8StackPopMul(uint8Stack *stack, unsigned char *data, unsigned int length)
{
    unsigned int i = 0;
    for(i = 0; i<length; i++)
    {
        if(uint8StackGetDeep(stack) == 0)
        {
            return STACK_EMPTY;
        }
        else
        {
            stack->top --;
            *data = stack->data[stack->top];
            stack->data[stack->top] = 0;
            data ++;
        }
    }
    return STACK_FINISH;
}


/*
*******************************************************************************
** Name :   8bits Get the stack deep
** Input0:  (*stack)Stack pointer
** return:  The deep of stack
*******************************************************************************
*/
unsigned int uint8StackGetDeep(uint8Stack *stack)
{
    return stack->top;
}

//======================================================================================================================================//
//--------------------------------------------------------------------------------------------------------------------------------------//
//======================================================================================================================================//

/*
*******************************************************************************
**Name : 32bits Stack initializaton
**Input: Stack pointer
**Return: None
*******************************************************************************
*/
void uint32StackInit(uint32Stack *stack)
{
		static unsigned int i = 0;
    stack->top = 0;
		for(i = 0; i<STACK_MAX_DEEP; i++)
		{
			stack->data[i] = 0;
		}
}

/*
*******************************************************************************
**Name : 32bits Stack Clear
**Input: Stack pointer
**Return: None
*******************************************************************************
*/
void uint32StackClear(uint32Stack *stack)
{
		static unsigned int i = 0;

		for(i = 0; i<STACK_MAX_DEEP; i++)
		{
			stack->data[i] = 0;
		}
    stack->top = 0;
}

/*
*******************************************************************************
** Name :  8bits Stack Push data
** Input0: (*stack)Stack pointer
** Input1: (data)One data be pushed int stack
** Return: Stack states
**         (STACK_FINISH): The data has been pushed into stack
**         (STACK_FULL)  : The stack had be STACK_FULL,can't push the data into stack
*******************************************************************************
*/
StackStates uint32StackPush(uint32Stack *stack, unsigned int data)
{
    if(uint32StackGetDeep(stack) >= STACK_MAX_DEEP)   // If stack has been STACK_FULL, return "STACK_FULL"
    {
        return STACK_FULL;
    }
    else
    {    
        stack->data[stack->top] = data;
        stack->top ++;
        return STACK_FINISH;
    }
}

/*
*******************************************************************************
** Name :  32bits Stack Push Multiple data
** Input0: (*stack)Stack pointer
** Input1: (*data)The pointer of data
** Input2: (length)The length of data
** Return: Stack states
**         (STACK_FINISH): The data has been pushed into stack
**         (STACK_FULL)  : The stack had be STACK_FULL,can't push the data into stack
*******************************************************************************
*/
StackStates uint32StackPushMul(uint32Stack *stack, unsigned int *data, unsigned int length)
{
    unsigned int i = 0;
    for(i = 0; i<length; i++)
    {    
        if(uint32StackGetDeep(stack) >= STACK_MAX_DEEP)
        {
            return STACK_FULL;
        }
        else
        {
            stack->data[stack->top] = *data;
            stack->top ++;
        }
        data ++;
    }
    return STACK_FINISH;
}

/*
*******************************************************************************
** Name :   32bits Stack Pop data 
** Input0: (*stack) Stack pointer
** Input1: (*data) The pointer which stack pop the data put into it.
** Return : Stack states
**          (FNISH): The data has been pop from stack,and put into *data.
**          (STACK_EMPTY): The stack is STACK_EMPTY,can't pop data from it.
*******************************************************************************
*/
StackStates uint32StackPop(uint32Stack *stack, unsigned int *data)
{
    if(uint32StackGetDeep(stack) == 0)
    {
        return STACK_EMPTY;
    }
    else
    {
        stack->top --;
        *data = stack->data[stack->top];
        stack->data[stack->top] = 0;
        return STACK_FINISH;
    }
}


/*
*******************************************************************************
** Name :   32bits Stack Pop Multiple data 
** Input0: (*stack) Stack pointer
** Input1: (*data) The pointer of data
** Input2: (length)The length of data be pop
** Return : Stack states
**          (FNISH): The data has been pop from stack,and put into *data.
**          (STACK_EMPTY): The stack is STACK_EMPTY,can't pop data from it.
*******************************************************************************
*/
StackStates uint32StackPopMul(uint32Stack *stack, unsigned int *data, unsigned int length)
{
    unsigned int i = 0;
    for(i = 0; i<length; i++)
    {
        if(uint32StackGetDeep(stack) == 0)
        {
            return STACK_EMPTY;
        }
        else
        {
            stack->top --;
            *data = stack->data[stack->top];
            stack->data[stack->top] = 0;
            data ++;
        }
    }
    return STACK_FINISH;
}

/*
*******************************************************************************
** Name :   32bits Get the stack deep
** Input0:  (*stack)Stack pointer
** return:  The deep of stack
*******************************************************************************
*/
unsigned int uint32StackGetDeep(uint32Stack *stack)
{
    return stack->top;
}


//======================================================================================================================================//
//--------------------------------------------------------------------------------------------------------------------------------------//
//======================================================================================================================================//

void voidStackInit(voidStack *stack)
{
		static unsigned int i = 0;
		stack->top = 0;
		for(i = 0; i<STACK_MAX_DEEP; i++)
		{
			stack->pointer[i] = (void *)0;
		}
}

void voidStackClear(voidStack *stack)
{
		static unsigned int i = 0;
		stack->top = 0;
		for(i = 0; i<STACK_MAX_DEEP; i++)
		{
			stack->pointer[i] = (void *)0;
		}
}

StackStates voidStackPush(voidStack *stack, void *pointer)
{
    if(voidStackGetDeep(stack) >= STACK_MAX_DEEP)   // If stack has been STACK_FULL, return "STACK_FULL"
    {
        return STACK_FULL;
    }
    else
    {    
        stack->pointer[stack->top] = pointer;
        stack->top ++;
        return STACK_FINISH;
    }
}


StackStates voidStackPop(voidStack *stack, void **pointer)
{
	  if(voidStackGetDeep(stack) == 0)
    {
        return STACK_EMPTY;
    }
    else
    {
        stack->top --;
        *pointer = stack->pointer[stack->top];
        stack->pointer[stack->top] = (void *)0;
        return STACK_FINISH;
    }
}


unsigned int voidStackGetDeep(voidStack *stack)
{
		return stack->top;
}

