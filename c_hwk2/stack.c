/**********************************************************
** Project: c_hwk2
** Advanced C, Hwk 2 : A circularized doubly linked list
** containing stock names and quotes.
** This source file is for the stack.h header.
**
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/**
Function push. Inserts a stack node into the top of the stack.
If possible, allocates dynamically a stack node and inserts it into the stack.
*/
S_NODE* push(S_NODE* stack, double data)
{
    S_NODE* pnew;
    pnew = (S_NODE*) calloc(1, sizeof(S_NODE));
    if(!pnew)
    {
        printf("Error: Not enough memory to push stack node.\n");
        exit(1);
    }
    pnew->stock_quote = data;
    pnew->next = stack;
    stack = pnew;
    return stack;
}

/**
 Function pop. Pops a node off the stack and returns it as a pointer to the caller.
*/
S_NODE* pop(S_NODE** stack)
{
    S_NODE *first;
    if(*stack == NULL)
    {
        return NULL;
    }
    first = *stack;
    *stack = (*stack)->next;
    first->next = NULL;
    return first;
}


/**
 Function peek. Returns the value of what is at the top of the stack, or -1 if it's empty.
*/
double peek(S_NODE* stack)
{
    if(stack == NULL)
    {
        return -1;
    }
    return stack->stock_quote;
}

/**
 Function free_stack. Entirely frees the dynamically allocated memory of the specified number of nodes, starting from top.
 */
void free_stack (S_NODE* s_node, int num_nodes)
 {
     for (int i =0; i<num_nodes; i++)
        {
           free(pop(&(s_node))); // free stack node
        }
 }
