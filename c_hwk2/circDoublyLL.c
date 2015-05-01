/**********************************************************
** Project: c_hwk2
** Advanced C, Hwk 2 : A circularized doubly linked list
** containing stock names and quotes.
** This source file is for the circDoublyLL.h header.
**
***********************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "circDoublyLL.h"

/**
 Function init_list. Initializes a circular doubly linked list with one sentinel node.
 It will skip the dummy node except to simplify the insert (/delete) operations.
*/
LL_NODE* init_list(void)
{
    LL_NODE* list;
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

/**
 Function ll_insert. Takes in a stock name and quote, and inserts it into the list. The function
 checks if the stock name is a duplicate and if so, it does not allocate an additional list node
 but rather simply stores the quote onto the existing list node's stack.
 Function returns 1 if duplicate, 0 otherwise.
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

/**
 Function ll_traverse_forw. Traverses forward the list and prints each node's stock name and entire contents.
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
        int num_quotes = list->quote_count;
        for(int i =0; i<num_quotes; i++)
        {
            printf("\t%.2f\n",curr->stock_quote);
            curr = curr->next;
        }
        list = list->forw;
    }
}

/**
 Function ll_traverse_back. Function traverses backwards and prints the stock name until it hits the sentinel node.
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

/**
    Function ll_printStockInfo. Prints stock names only between 2 integers, between zero and the loaded number
    of stocks by using the sentinel node's count value to see the number of nodes in the list.
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

/**
 Function print_n_stocks prints some number of stocks chosen by the user, displaying the
 stock name and its most recent quote. The user inputs have both been previously
 validated. This function will print the shortest path between 2 chosen stocks,
 whether it's t the front or to the back traversal.
*/
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
        while(strcmp(stock_from, curr->stock_name) < 0)
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

/**
 Function print_n_quotes. Prints the chosen stock's name and some number of quotes, which have both been previously
 validated.
*/
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

/**
Function free_list will free all dynamically allocated contents of the list and the stacks within each list entry.
*/
void free_list(LL_NODE* list)
{
    LL_NODE* pWalk = list->forw;
    S_NODE* temp = NULL;

    while(pWalk->stock_name[0] != DUMMY_TRAILER)
    {
        for (int i =0; i<pWalk->quote_count; i++)
        {
           free(pop(&(pWalk->quote_stack))); // free stack node
        }
        free(pWalk); // free list node
        pWalk = pWalk->forw;
    }
    free(list);
}
