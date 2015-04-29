#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "circDoublyLL.h"

/***************************************************
    Initialization of a circularly doubly-linked
    list with one sentinel node
*/
LL_NODE* init_list(void)
{
    LL_NODE *list;

    // allocate the sentinel node
    list = (LL_NODE *) malloc(sizeof (LL_NODE));
    if (!list)
    {
        printf("Error in init_list!\n");
        exit(1);
    }
    list->stock_name[0] = DUMMY_TRAILER;
    list->stock_name[1] = '\0';
    list->quote_count = 0;
    list->forw = list;
    list->back = list;

    return list;
}

/***************************************************
    Insert a node in a sorted circularly
    doubly-linked list with one sentinel node
        return 1 - if duplicate
        return 0 - otherwise
*/
int ll_insert(LL_NODE *list, char* new_stock_name)
{
    LL_NODE* curr = list->forw;
    LL_NODE* prev = list;
    LL_NODE* pnew;
    int   duplicate = 1;

    // search
    while (strcmp(new_stock_name,curr->stock_name) > 0)
    {
        prev = curr;
        curr = curr->forw;
    }

    if (strcmp(new_stock_name, curr->stock_name) )
    {
        duplicate = 0; // not a duplicate
        pnew = (LL_NODE *) malloc(sizeof (LL_NODE));
        if (!pnew)
        {
            printf("Fatal memory allocation error in insert!\n");
            exit(3);
        }
        strcpy(pnew->stock_name, new_stock_name);
        pnew->forw = curr;
        pnew->back = prev;
        prev->forw = pnew;
        curr->back = pnew;
    }
    return duplicate;
}

/***************************************************
    Traverses forward a circularly doubly-linked
    list with one sentinel node to print out the
    contents of each node
*/
void ll_traverse_forw(LL_NODE *list)
{
    putchar('\n');
    list = list->forw; // skip the dummy node
    while (list->stock_name[0] != DUMMY_TRAILER)
    {
        printf("%s\n", list->stock_name);
        list = list->forw;
    }
    return;
}

/***************************************************
    Traverses backward a circularly doubly-linked
    list with one sentinel node to print out the
    contents of each node
*/
void ll_traverse_back(LL_NODE *list)
{
    putchar('\n');
    list = list->back; // skip the dummy node
    while (list->stock_name[0] != DUMMY_TRAILER)
    {
        printf("%s\n", list->stock_name);
        list = list->back;
    }
    return;
}

