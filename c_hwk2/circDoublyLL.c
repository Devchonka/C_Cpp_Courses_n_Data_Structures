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
    list = (LL_NODE *) malloc(sizeof(LL_NODE));
    if(!list)
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
int ll_insert(LL_NODE* list, char* new_stock_name, double quote)
{
    LL_NODE* dummy_node = list;
    LL_NODE* curr = list->forw;
    LL_NODE* prev = list;
    LL_NODE* pnew;
    int   duplicate = 1;
    // search
    while(strcmp(new_stock_name,curr->stock_name) > 0)
    {
        prev = curr;
        curr = curr->forw;
    }
    if(strcmp(new_stock_name, curr->stock_name))   // strcmp returns 0 if equal
    {
        duplicate = 0; // not a duplicate
        pnew = (LL_NODE *) malloc(sizeof(LL_NODE));
        if(!pnew)
        {
            printf("Fatal memory allocation error in insert!\n");
            exit(3);
        }
        strcpy(pnew->stock_name, new_stock_name);
        pnew->forw = curr;
        pnew->back = prev;
        prev->forw = pnew;
        curr->back = pnew;
        dummy_node->quote_count++;
        pnew->quote_stack = push(pnew->quote_stack, quote);
        pnew->quote_count++;
    }
    else
    {
        curr->quote_stack = push(curr->quote_stack, quote);
        curr->quote_count++;
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
    S_NODE* curr;
    while(list->stock_name[0] != DUMMY_TRAILER)
    {
        printf("%s\n", list->stock_name);
        curr = list->quote_stack;
        list = list->forw;
    }
}
/**
    Prints stock names only
*/

void ll_printStockInfo(LL_NODE* list, int from, int to)
{
    putchar('\n');
    if((from<0) || (to<0) || (from>list->quote_count) || (to>list->quote_count))
    {
        printf("Error: program may display only entries between 0 and %d for %s.\n", list->quote_count, list->stock_name);
    }
    from = (from<0) ? 0 : from;
    to = (to<0) ? 0 : to;
    from = (from>list->quote_count) ? list->quote_count : from;
    to = (to>list->quote_count) ? list->quote_count : to;
    if(from < to)
    {
        for(int i=from; i < to; i++)
        {
            if(list->stock_name[0] == DUMMY_TRAILER)
            {
                list = list->forw;
            }
            printf("%s\t", list->stock_name);
            list = list->forw;
        }
    }
    else
    {
        for(int i=from; i > to; i--)
        {
            if(list->stock_name[0] == DUMMY_TRAILER)
            {
                list = list->back;
            }
            printf("%s\t", list->stock_name);
            list = list->back;
        }
    }
    putchar('\n');
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
    while(list->stock_name[0] != DUMMY_TRAILER)
    {
        printf("%s\n", list->stock_name);
        list = list->back;
    }
    return;
}

void print_n_stocks(LL_NODE* list, char* stock_from, char* stock_to) // menu option 2
{
    LL_NODE* curr;
    if(strcmp(stock_from, stock_to)<=0)  //go forward
    {
        curr = list->forw;
        while(strcmp(stock_from,curr->stock_name) > 0)
        {
            curr = curr->forw; // curr points to stock_from
        }
        while(strcmp(curr->stock_name, stock_to) <= 0)
        {
            printf("%s (%.2f)\n", curr->stock_name, curr->quote_stack->stock_quote);
            curr = curr->forw;
        }
    }
    else // go back
    {
        curr = list->back;
        while(strcmp(stock_from,curr->stock_name) < 0)
        {
            curr = curr->back; // curr points to stock_from
        }
        while(strcmp(curr->stock_name, stock_to) >= 0)
        {
            printf("%s (%.2f)\n", curr->stock_name, curr->quote_stack->stock_quote);
            curr = curr->back;
        }
    }
}

void print_n_quotes(LL_NODE* list, char* stock_name, int num_quotes) // option 1
{
    LL_NODE* curr = list->forw;
    S_NODE* curr_stack;
    while(strcmp(stock_name,curr->stock_name) > 0)
    {
        curr = curr->forw; // curr points to stock_from
    }
    printf("%s\n", curr->stock_name);
    curr_stack = curr->quote_stack;
    for(int i =0; i <num_quotes; i++)
    {
        printf("\t%.2f\n", curr_stack->stock_quote);
        curr_stack = curr_stack->next;
    }
}
