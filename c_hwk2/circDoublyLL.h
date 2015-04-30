#ifndef CIRC_DOUBLY_LL
#define CIRC_DOUBLY_LL

#include <stdbool.h>
#include "stack.h"

#define DUMMY_TRAILER '\177'// octal ASCII code of last character in the ASCII table

typedef struct ll_node LL_NODE;
struct ll_node
{
    char  stock_name[8];
    int quote_count;
    S_NODE* quote_stack;

    LL_NODE *forw;
    LL_NODE *back;
};

LL_NODE* init_list(void);
int   ll_insert(LL_NODE*, char*, double);
void  ll_traverse_forw(LL_NODE*);
void  ll_traverse_back(LL_NODE*);
void ll_printStockInfo(LL_NODE*, int, int);

void print_n_stocks(LL_NODE*, char*, char*); // option 2
void print_n_quotes(LL_NODE*, char*, int); // option 1

#endif // CIRC_DOUBLY_LL
