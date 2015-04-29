#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "circDoublyLL.h"

/***************************************************
    Initialization of a circularly doubly-linked
    list with one sentinel node
*/
NODE *init_list(void)
{
    NODE *list;

    // allocate the sentinel node
    list = (NODE *) malloc(sizeof (NODE));
    if (!list)
    {
        printf("Error in init_list!\n");
        exit(1);
    }
    list->data[0] = DUMMY_TRAILER;
    list->data[1] = '\0';
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
int insert(NODE *list, char *data)
{
    NODE *curr = list->forw;
    NODE *prev = list;
    NODE *pnew;
    int   duplicate = 1;

    // search
    while (strcmp(data,curr->data) > 0)
    {
        prev = curr;
        curr = curr->forw;
    }

    if (strcmp(data, curr->data) )
    {
        duplicate = 0; // not a duplicate
        pnew = (NODE *) malloc(sizeof (NODE));
        if (!pnew)
        {
            printf("Fatal memory allocation error in insert!\n");
            exit(3);
        }
        strcpy(pnew->data, data);
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
void traverse_forw(NODE *list)
{
    putchar('\n');
    list = list->forw; // skip the dummy node
    while (list->data[0] != DUMMY_TRAILER)
    {
        printf("%s\n", list->data);
        list = list->forw;
    }
    return;
}

/***************************************************
    Traverses backward a circularly doubly-linked
    list with one sentinel node to print out the
    contents of each node
*/
void traverse_back(NODE *list)
{
    putchar('\n');
    list = list->back; // skip the dummy node
    while (list->data[0] != DUMMY_TRAILER)
    {
        printf("%s\n", list->data);
        list = list->back;
    }
    return;
}

