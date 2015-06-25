/**
    File queue.c is the source for the queue.h header. It holds definitions for the queue functions.
*/

#include "queue.h"

/***************************************************
    Queue Insert: insert at the end
*/
void enqueue(qNODE **queue, qNODE **rear, qDATA data)
{
    qNODE *pnew;
    pnew = (qNODE *) malloc(sizeof(qNODE));
    if(!pnew)
    {
        printf("... error in enqueue!\n");
        exit(1);
    }
    pnew->data = data;
    //printf("\nEnqueued pnew->data of line %d\n", pnew->data.line);
    pnew->next = NULL;
    if(*queue == NULL)
    {
        *queue = pnew;
    }
    else
    {
        (*rear)->next = pnew;
    }
    *rear = pnew;
    return;
}

/***************************************************
    Queue Delete: remove the first node
*/
qNODE *dequeue(qNODE **queue, qNODE **rear)
{
    qNODE *first;
    if(*queue == NULL)
    {
        return NULL;
    }
    first = *queue;
    *queue = (*queue)->next;
    if(*queue == NULL)
    {
        *rear = NULL;
    }
    first->next = NULL;
    return first;
}

/**
    Function allows to peek the front of the queue's line number to prevent repetitions.
*/
int peek_lineNum(qNODE* q_rear)
{
    if(q_rear == NULL)
    {
        return -1;
    }
    return q_rear->data.line;
}
