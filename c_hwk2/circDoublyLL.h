#ifndef CIRC_DOUBLY_LL
#define CIRC_DOUBLY_LL


#define DUMMY_TRAILER '\177'// octal ASCII code of last character in the ASCII table

typedef struct node NODE;
struct node
{
    char  data[20];
    NODE *forw;
    NODE *back;
};


#endif // CIRC_DOUBLY_LL
