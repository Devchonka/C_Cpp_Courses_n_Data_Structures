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
    DATA STRUCTURES:
        x 2) Create LL node containing stock symbol, pointer to stack of quote nodes, pointers to prev,next LL nodes, count of quotes
        x 3) Create stack node containing stock quote, pointer to next stack node
        x 4) Create circularly doubly LL (sorted by stock name) w/ 1 sentinel node (each stack is created within LL node)
    x 6) Read data into LL and stacks
    MENU:
        7) Prompt user for stock symbol and positive integer (# recent quotes to show) until the user enters
        some sort of sentinel which you may decide upon
        8) Prompt user for 2 stock symbols, display sub-list of stocks (name +most recent quote), ascending OR descending,
         until the user enters some sort of sentinel which you may decide upon
    9) Free all dynamically allocated memory

    10) Check memory leak detection using VALGRIND


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
void read_file(char*, LL_NODE**);
void user_menu(LL_NODE*, char*);
bool validate_user_command(int, char*);


int main()
{
    char* fname_input = get_user_fname();
    LL_NODE* list = init_list();
    read_file(fname_input,&list);
    /** Code to peek at top val in stack
    double topVal;
    topVal = peek(stack);
       if(topVal==-1)
        printf("Stack is empty!\n");
        else
    printf("%.2f\n", topVal);
    */
    // LL stuff
    user_menu(list, fname_input);
    /*ll_traverse_forw(list);

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
    FILE* file = fopen(strtok(fname, "\n"), "r");
    if((fname[0]=='\n'))
    {
        return true;
    }
    else if(file)
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


void read_file(char* fname_in, LL_NODE** list)
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
    double quote;
    char name[6];
    int duplicate;
    while(fgets(line, sizeof(line), ifp))
    {
        if(line[0] != '\n')
        {
            sscanf(line, "%6[^ ]%*c%lf", name, &quote);
            duplicate = ll_insert(*list, name, quote);
            /*
            if(duplicate)
            {
            printf("%s already in the list!\n", name);
            }
            */
        }
        index++;
    }
    fclose(ifp);
}

/**
Prompt user for stock symbol and positive integer (# recent quotes to show) until the user enters
        some sort of sentinel which you may decide upon
Prompt user for 2 stock symbols, display sub-list of stocks (name +most recent quote), ascending OR descending,
         until the user enters some sort of sentinel which you may decide upon
*/
void user_menu(LL_NODE* list, char* fname_input)
{
    int choice, BUFFER_SIZE = 100; char command[BUFFER_SIZE];

    printf("********* MENU ************\n");
    printf("Your collection of %d unique stocks from %s is: ", list->quote_count, fname_input);

    ll_printStockNames(list, 0, list->quote_count);
    putchar('\n');
    printf("1. Show some number of most recent quotes for a particular stock.\n");
    printf("2. Show a portion of stocks between two chosen stock symbols.\n");
    printf("3. Quit.\n");
    printf("Enter an option (1, 2, or 3) :\n");

    fgets(command, BUFFER_SIZE, stdin);


    do
    {


    }
    while(!validate_user_command(choice, command));
    }

bool validate_user_command(int choice, char* command)
{

    return true;
}
