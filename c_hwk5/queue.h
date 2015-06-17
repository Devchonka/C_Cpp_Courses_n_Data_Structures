/**
    This file contains the queue node struct and the queue node data struct.
*/
#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
typedef struct qnode qNODE;
typedef struct qdata qDATA;

struct qdata
{
    int page;
    int line;
};

struct qnode
{
    qDATA data;
    struct qnode *next;
};

qNODE* dequeue(qNODE**, qNODE**);
void enqueue(qNODE**, qNODE**, qDATA);

#endif // QUEUE_H
