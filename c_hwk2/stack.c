#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/***************************************************
    Stack Insert: insert in the beginning - data is the stack_quote
*/
S_NODE* push(S_NODE* stack, double data)
{
    S_NODE* pnew;
    pnew = (S_NODE*) malloc(sizeof(S_NODE));
    if(!pnew)
    {
        printf("... error in push!\n");
        exit(1);
    }
    pnew->stock_quote = data;
    pnew->next = stack;
    stack = pnew;
    return stack;
}

/***************************************************
    Stack Delete: delete the first S_NODE
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


/***************************************************
    Stack Peek: Peek at the first S_NODE
*/
double peek(S_NODE* stack)
{
    if(stack == NULL)
    {
        return -1;
    }
    return stack->stock_quote;
}


