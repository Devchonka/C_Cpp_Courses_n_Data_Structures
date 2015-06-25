/**
    File BST.h is the header file for the binary tree node data structure definition and function declarations.
    It holds definitions for the binary search tree functions.
*/

#ifndef BST_H
#define BST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "queue.h"

#define MAX 50

typedef struct bstNode bstNODE;
typedef struct bstData bstDATA;

/**
    Data struct that stores the word, its frequency of appearance, and pointers to the front and back of its queue.
*/
struct bstData
{
    char* word;
    int freq;
    qNODE* q_front;
    qNODE* q_rear;
};

/**
    Data struct that holds a copy of the data contained per node, as well as a left and right pointer for the BST tree.
*/
struct bstNode
{
    bstDATA bstData;
    struct bstNode* left;
    struct bstNode* right;
};

bstNODE* buildBinaryTree();
void printTreeInorder(bstNODE*, FILE*);
void insert_bstNode(bstNODE**, char*, int, int);
bstNODE* find(bstNODE*, char*);
void* freeTree(bstNODE* root);

#endif // BST_H
