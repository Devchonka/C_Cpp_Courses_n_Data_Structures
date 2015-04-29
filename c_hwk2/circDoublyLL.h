#ifndef CIRC_DOUBLY_LL
#define CIRC_DOUBLY_LL


#define DUMMY_TRAILER '\177'// octal ASCII code of last character in the ASCII table

typedef struct ll_node LL_NODE;
struct ll_node
{
    char  stock_name[8];
    int quote_count;
    LL_NODE *forw;
    LL_NODE *back;
};

LL_NODE* init_list(void);
int   ll_insert(LL_NODE*, char*);
void  ll_traverse_forw(LL_NODE*);
void  ll_traverse_back(LL_NODE*);


#endif // CIRC_DOUBLY_LL
