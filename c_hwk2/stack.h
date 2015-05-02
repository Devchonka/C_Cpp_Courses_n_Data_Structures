/**********************************************************
** Project: c_hwk2
** Advanced C, Hwk 2 : A circularized doubly linked list
** containing stock names and quotes.
** This header file is for the stack functions.
**
***********************************************************/

#ifndef MY_STACK_H
#define MY_STACK_H

/******************
** STACK NODE STRUCT
*******************/
typedef struct s_node S_NODE; // for stack node
struct s_node
{
    double stock_quote;
    struct s_node* next;
};


/******************
** STACK FUNCTIONS
*******************/
S_NODE* push(S_NODE*, double);
S_NODE* pop(S_NODE**);
double peek(S_NODE*);
void free_stack (S_NODE*, int);

#endif // MY_STACK_H
