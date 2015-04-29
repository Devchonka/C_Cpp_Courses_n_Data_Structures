/*********************************************************************************
** CIS 26B                                                            Spring, 2015
** Advanced C
******************
**
** Homework 2: STOCKS
**        A Circularly Doubly Linked List of Stacks
**
**********************************************************************************
**  Written By: Menyaylenko, Elena
**
**  Date:               04/15/2015
**  IDE (compiler):     GNU GCC Compiler, Unix OS
**
    Procedure:
    x 1) Read fname from user, if blank, use STOCKS.TXT (Finish Monday)
    DATA STRUCTURES: (Finish Tuesday)
        2) Create LL node containing stock symbol and pointer to stack of quote nodes, pointers to prev,next LL nodes
        x 3) Create stack node containing stock quote, pointer to next stack node
        4) Create circularly doubly LL (sorted by stock name) w/ 1 sentinel node
        5) Create stack
    6) Read data into LL and stacks
    MENU: (Finish Wedn)
        7) Prompt user for stock symbol and positive integer (# recent quotes to show) until the user enters
        some sort of sentinel which you may decide upon
        8) Prompt user for 2 stock symbols, display sub-list of stocks (name +most recent quote), ascending OR descending,
         until the user enters some sort of sentinel which you may decide upon

    9) Check memory leak detection using VALGRIND


    To compile code:
        gcc -std=c99  *.c *.h -o c_hwk2
    To check memory leaks with Valgrind:
        valgrind --tool=memcheck --leak-check=yes ./c_hwk2
************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "stack.h"
#include "circDoublyLL.h"

/* Functions to get input file name from user  */
char* get_user_fname();
bool validate_user_fname(char*);
void read_file(char*, S_NODE**, LL_NODE**);
void user_menu();


int main()
{
    char* fname_input = get_user_fname();

    LL_NODE* list = init_list();
    S_NODE* stack = NULL;


    read_file(fname_input, &stack, &list);

    /** Code to peek at top val in stack
    double topVal;
    topVal = peek(stack);
       if(topVal==-1)
        printf("Stack is empty!\n");
        else
    printf("%.2f\n", topVal);
    */


    // LL stuff


    user_menu();


    /*
    ll_traverse_forw(list);
    ll_traverse_back(list);
    */



    return 0;
}

/******************************
**     MENU FUNCTIONS
*******************************/

char* get_user_fname()
{
    int BUFFER_SIZE = 25;
    char fname_input[BUFFER_SIZE];
    do
    {
        printf("%s", "Enter input filename: ");
        fgets(fname_input, BUFFER_SIZE, stdin);
    }
    while(!validate_user_fname(fname_input));
    return (fname_input[0]=='\n') ? "stocks.txt": fname_input;
}

bool validate_user_fname(char* fname)
{
    FILE* file;
    if((fname[0]=='\n'))
    {
        return true;
    }
    else if(fopen(strtok(fname, "\n"), "r"))
    {
        if(file != NULL)
        {
            fclose(file);
        }
        return true;
    }
    else
    {
        printf("File %s cannot be opened. Try again or click ENTER to read default file stocks.txt\n", strtok(fname, "\n"));
        return false;
    }
}


void read_file(char* fname_in, S_NODE** stack, LL_NODE** list)
{
    char line[31];
    FILE* ifp;
    ifp = fopen(fname_in, "r");
    int index = 0;

    if(fgets(line, sizeof(line), ifp)==NULL)
    {
        fprintf(stderr, "Error: empty input file %s\n", fname_in);
        exit(EXIT_FAILURE);
    }

double quote; char name[6]; int duplicate;
    while(fgets(line, sizeof(line), ifp))
    {
        if(line[0] != '\n')
        {
            sscanf(line, "%6[^ ]%*c%lf", name, &quote);

            duplicate = ll_insert(*list, name);
        if(duplicate)
        {
            printf("%s already in the list!\n", name);
        }

            *stack = push(*stack, quote);
        }
        index++;
    }
    fclose(ifp);
}

void user_menu()
{
    printf("Here is the user menu...");
}
