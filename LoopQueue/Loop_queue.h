#ifndef _RING_QUEUE_H_
#define _RING_QUEUE_H_

#define uint32 unsigned int
#define uint8 unsigned char
#define QUEUE_MAX_LENGTH  256

typedef enum _LoopQueueStateType
{
    EMPTY = 0x50000000,
    FULL,
    DONE,
    UNDONE, 
}LoopQueueStateType;

typedef struct _LoopQueue
{
    uint8 putIndex;
    uint8 getIndex;
    uint32 dataNumber;
    uint8 queueFifo[QUEUE_MAX_LENGTH];
}LoopQueue;


extern void LoopQueueInit(LoopQueue *queue);
extern void LoopQueueClear(LoopQueue *queue);
extern LoopQueueStateType LoopQueueWrite(LoopQueue *queue, uint8 *data, uint32 length);
extern LoopQueueStateType LoopQueueRead(LoopQueue *queue, uint8 *addr ,uint32 length);
extern LoopQueueStateType LoopQueueWriteOne(LoopQueue *queue, uint8 data);
extern LoopQueueStateType LoopQueueReadOne(LoopQueue *queue, uint8 *addr);
extern uint32 LoopQueueGetLength(LoopQueue *queue);

#endif



