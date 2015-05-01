/**********************************************************
** Project: c_hwk2
** Advanced C, Hwk 2 : A circularized doubly linked list
** containing stock names and quotes.
** This header file is for the linked list functions.
**
***********************************************************/
#ifndef CIRC_DOUBLY_LL
#define CIRC_DOUBLY_LL

#include <stdbool.h>
#include "stack.h"

#define DUMMY_TRAILER '\177'// octal ASCII code of last character in the ASCII table

/******************
** LIST NODE STRUCT
*******************/
typedef struct ll_node LL_NODE;
struct ll_node
{
    char  stock_name[8];
    int quote_count;
    S_NODE* quote_stack;

    LL_NODE *forw;
    LL_NODE *back;
};

/******************
** LIST NODE STRUCT
*******************/
LL_NODE* init_list(void);
int   ll_insert(LL_NODE*, char*, double);
void  ll_traverse_forw(LL_NODE*);
void  ll_traverse_back(LL_NODE*);
void ll_printStockInfo(LL_NODE*, int, int);

void print_n_stocks(LL_NODE*, char*, char*); // option 2
void print_n_quotes(LL_NODE*, char*, int); // option 1

void free_list(LL_NODE*);

#endif // CIRC_DOUBLY_LL
