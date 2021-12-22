#include "Loop_queue.h"


void LoopQueueInit(LoopQueue *queue)
{
	uint32 i = 0;
  queue->getIndex = 0;
	queue->putIndex = 0;
	queue->dataNumber = 0;
	for(i = 0; i<QUEUE_MAX_LENGTH; i++)
	{
		queue->queueFifo[i] = 0;   // Clear all fifo
	}
}

void LoopQueueClear(LoopQueue *queue)
{
    unsigned int clearIndex;

    queue->getIndex = 0;
    queue->putIndex = 0;
    for(clearIndex = 0; clearIndex < QUEUE_MAX_LENGTH ; clearIndex ++)
    {
        queue->queueFifo[clearIndex] = 0;
    }
    queue->dataNumber = 0;
}

LoopQueueStateType LoopQueueWrite(LoopQueue *queue, uint8 *data, uint32 length)
{
    uint32 i = 0;
    if(length > (QUEUE_MAX_LENGTH - queue->dataNumber))   
    {
        return UNDONE;
    }
    for(i = 0; i<length ; i++)
    {
        if((QUEUE_MAX_LENGTH - queue->dataNumber) == 0)
        {
            return FULL;
        }
        queue->queueFifo[queue->putIndex] = *(data++);
        queue->dataNumber ++;
        if(queue->putIndex == QUEUE_MAX_LENGTH-1)
        {
           queue->putIndex = 0;
        }
        else
        {
           queue->putIndex ++;
        }
    }
    return DONE;
}

LoopQueueStateType LoopQueueRead(LoopQueue *queue, uint8 *addr ,uint32 length)
{
    uint32 i = 0;

    if(queue->dataNumber == 0)
    {
        return EMPTY;
    }
    for(i = 0; i<length; i++)
    {
        if(queue->dataNumber == 0)
        {
            return UNDONE;
        }
        *addr++ = queue->queueFifo[queue->getIndex];
        queue->dataNumber --;
        if(queue->getIndex == QUEUE_MAX_LENGTH-1)
        {
           queue->getIndex = 0;
        }
        else
        {
           queue->getIndex ++;
        }
    }
    return DONE;
}

LoopQueueStateType LoopQueueWriteOne(LoopQueue *queue, uint8 data)
{
    if((QUEUE_MAX_LENGTH - queue->dataNumber) == 0)
    {
        return FULL;
    }
    queue->queueFifo[queue->putIndex] = data;
    queue->dataNumber ++;
    if(queue->putIndex == QUEUE_MAX_LENGTH-1)
    {
         queue->putIndex = 0;
    }
    else
    {
         queue->putIndex ++;
    }

    return DONE;
}

LoopQueueStateType LoopQueueReadOne(LoopQueue *queue, uint8 *addr)
{
    if(queue->dataNumber == 0)
    {
        return EMPTY;
    }
    *addr = queue->queueFifo[queue->getIndex];
    queue->dataNumber --;
    if(queue->getIndex == QUEUE_MAX_LENGTH-1)
    {
         queue->getIndex = 0;
    }
    else
    {
         queue->getIndex ++;
    }
    return DONE;
}

uint32 LoopQueueGetLength(LoopQueue *queue)
{
    return queue->dataNumber;
}

