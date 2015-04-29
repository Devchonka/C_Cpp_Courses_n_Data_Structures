#ifndef MY_STACK_H
#define MY_STACK_H

/******************
** Node data struct
*******************/
typedef struct s_node S_NODE; // for stack node
struct s_node
{
    double stock_quote;
    struct s_node* next;
};


/******************
** stack functions
*******************/
S_NODE* push(S_NODE*, double);
S_NODE* pop(S_NODE**);
double peek(S_NODE*);

#endif // MY_STACK_H
