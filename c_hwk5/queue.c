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
