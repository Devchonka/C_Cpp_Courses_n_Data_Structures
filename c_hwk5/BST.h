#ifndef BST_H
#define BST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "queue.h"

#define MAX 50

typedef struct bstNode bstNODE;
typedef struct bstData bstDATA;

struct bstData
{
    char* word;
    int freq;
    qNODE* q_front;
    qNODE* q_rear;
};

struct bstNode
{
    bstDATA bstData;
    struct bstNode *left;
    struct bstNode *right;
};

bstNODE* buildBinaryTree();
void printTreeInorder(bstNODE*);
int insert(bstNODE**, bstDATA);
bstNODE *find(bstNODE*, char*);

#endif // BST_H
