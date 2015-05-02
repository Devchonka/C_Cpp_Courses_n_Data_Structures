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
    1) Read fname from user, if blank, use STOCKS.TXT (Finish Monday)
    DATA STRUCTURES:
        2) Create LL node containing stock symbol, pointer to stack of quote nodes, pointers to prev,next LL nodes, count of quotes
        3) Create stack node containing stock quote, pointer to next stack node
        4) Create circularly doubly LL (sorted by stock name) w/ 1 sentinel node (each stack is created within LL node)
    6) Read data into LL and stacks
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
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "stack.h"
#include "circDoublyLL.h"

char* get_user_fname();
bool validate_user_fname(char*);
void read_file(char*, LL_NODE**);
void user_menu(LL_NODE*, char*);
char get_user_choice(char*, LL_NODE*);
bool validate_stock_name(LL_NODE*, char*);
bool validate_stock_num_quotes(LL_NODE*, char*, int);


/******************************
Function main. It gets the input file name from the user, initializes a list, reads the file provided by the user, and populates
the circularly linked list with stock names and quotes from the file. It presents the user with a menu to choose what they would
like displayed.
*******************************/
int main()
{
    char* fname_input = get_user_fname();
    LL_NODE* list = init_list();
    read_file(fname_input,&list);
    user_menu(list, fname_input);
    free_list(list);
    free(fname_input);
    return 0;
}

/******************************
**     INPUT FILE FUNCTIONS
*******************************/

/**
Function get_user_fname. Its a loop that prompts the user for an input file name to load the stock data, validating
the input.
*/
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
    char* fname_returned;
    if(fname_input[0]=='\n')
    {
        strcpy(fname_input, "stocks.txt");
    }
    fname_returned = (char*) calloc(strlen(fname_input)+1, sizeof(char));
    if(!fname_returned)
    {
        printf("Error: not enough memory for string allocation of filename.\n");
        exit(1);
    }
    strcpy(fname_returned, fname_input);
    return fname_returned;
}

/**
Function validate_user_fname. It checks that something is entered, and that the entered file exists and may be opened
in read mode.
*/
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

/**
Function read_file. Read a valid file and populates a list with stock names and quotes from parsing the data line by line.
*/
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
    while(fgets(line, sizeof(line), ifp))
    {
        if(line[0] != '\n')
        {
            sscanf(line, "%6[^ ]%*c%lf", name, &quote);
            ll_insert(*list, name, quote);
        }
        index++;
    }
    fclose(ifp);
}

/**********************************
**     MENU / VALIDATION FUNCTIONS
***********************************/

/**
Function user_menu. Prompts the user to either see a portion of the stocks with their most recent quote,
or to show a certain number of quotes for a certain stock, or to exit. It will reject other entries.
*/
void user_menu(LL_NODE* list, char* fname_input)
{
    int BUFFER_SIZE = 200, temp_stock_name_size = 30;
    char choice;
    do
    {
        choice = get_user_choice(fname_input, list);
        switch(choice)
        {
        case '1':
        {
            char user_input[BUFFER_SIZE], stock_name[temp_stock_name_size];
            int num_quotes;
            do
            {
                putchar('\n');
                printf("**See some number of most recent quotes from particular stock**\n");
                printf("\tEnter the stock name and number of quotes, in the form: STOCK_NAME NUMBER (ie GOOG 3):\t");
                fgets(user_input, BUFFER_SIZE, stdin);
                sscanf(user_input, "%[A-Z] %d", stock_name, &num_quotes);
            }
            while(!(validate_stock_name(list, stock_name)) || !(validate_stock_num_quotes(list, stock_name, num_quotes)));
            print_n_quotes(list, stock_name, num_quotes);
            break;
        }
        case '2':
        {
            char user_input[BUFFER_SIZE], stock_from[temp_stock_name_size], stock_to[temp_stock_name_size];
            do
            {
                putchar('\n');
                printf("**See stocks between 2 stock symbols along with their most recent quote (ie GOOG VZ)**\n");
                printf("***The shortest path will be displayed, forward or backward***\n");
                printf("\tEnter the range, in the form: STOCK_FROM STOCK_TO:\t");
                fgets(user_input, BUFFER_SIZE, stdin);
                sscanf(user_input, "%[A-Z] %[A-Z]", stock_from, stock_to);
            }
            while(!(validate_stock_name(list, stock_from)) || !(validate_stock_name(list, stock_to)));
            print_n_stocks(list, stock_from, stock_to);
            break;
        }
        case '3':
            break;
        default:
        {
            printf("Error in switch statement in user menu.\n");
            exit(EXIT_FAILURE);
        }
        }
    }
    while(choice!='3');
}

/**
 Function get_user_choice. Returns the validated choice that the user selected back to the user menu.
*/
char get_user_choice(char* fname_input, LL_NODE* list)
{
    int BUFFER_SIZE = 20;
    char choice, line[BUFFER_SIZE];
    do
    {
        putchar('\n');
        printf("********* MENU ************\n");
        printf("Your collection of %d unique stocks from %s is: ", list->quote_count, fname_input);
        ll_printStockInfo(list, 0, list->quote_count);
        putchar('\n');
        printf("   1. Show some number of most recent quotes for a particular stock.\n");
        printf("   2. Show portion of stocks + most recent quote between any 2 stock symbols.\n");
        printf("   3. Quit.\n");
        printf("Enter an option (1, 2, or 3) : ");
        fgets(line, BUFFER_SIZE, stdin);
        choice = (strlen(line)>2)? '0' : line[0];
    }
    while(choice<'1' || choice>'3');
    return choice;
}

/**
Function validate_stock_name. Validates the entered in name of a stock.
 Checks 2 conditions : first, if the stored string is between 2 and 5 long. If so, then it searches
 for the stock name in the list and returns true if found.
*/

bool validate_stock_name(LL_NODE* list, char* stock_name)
{
    bool valid = (strlen(stock_name) < 2 || (strlen(stock_name))>5)? false : true;
    if(valid)
    {
        LL_NODE* curr = list->forw;
        while(strcmp(stock_name,curr->stock_name) > 0)
        {
            curr = curr->forw;
        }
        valid = (strcmp(stock_name, curr->stock_name))? false: true;
    }
    if(!valid)
    {
        printf("\nPlease type in a correct existing stock name (displayed in main menu).\n");
    }
    return valid;
}

/**
Function validate__stock_num_quotes. It checks that a number is positive and is less than the number of stocks contained
in the stack for the stored data from the input file.
*/
bool validate_stock_num_quotes(LL_NODE* list, char* stock_name, int num_quotes)
{
    bool valid = (num_quotes>0)? true : false;
    LL_NODE* curr = NULL;
    if(valid)
    {
        curr = list->forw;
        while(strcmp(stock_name,curr->stock_name) > 0)
        {
            curr = curr->forw;
        }
        valid = (num_quotes <= curr->quote_count)? true: false;
    }
    if(!valid)
    {
        printf("\nPlease select at most the number of quotes recorded (%d) in %s.\n", curr->quote_count, stock_name);
    }
    return valid;
}

/**
elena@elena-e5250 ~/CodeBlocksProjects/c_hwk2 $ gcc -std=c99  *.c *.h -o c_hwk2
elena@elena-e5250 ~/CodeBlocksProjects/c_hwk2 $ valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./c_hwk2
==11356== Memcheck, a memory error detector
==11356== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==11356== Using Valgrind-3.10.0.SVN and LibVEX; rerun with -h for copyright info
==11356== Command: ./c_hwk2
==11356==
Enter input filename:
==11356== Syscall param open(filename) points to unaddressable byte(s)
==11356==    at 0x4F22620: __open_nocancel (syscall-template.S:81)
==11356==    by 0x4EB0FC7: _IO_file_fopen@@GLIBC_2.2.5 (fileops.c:228)
==11356==    by 0x4EA54A3: __fopen_internal (iofopen.c:90)
==11356==    by 0x401266: validate_user_fname (in /home/elena/CodeBlocksProjects/c_hwk2/c_hwk2)
==11356==    by 0x4011B3: get_user_fname (in /home/elena/CodeBlocksProjects/c_hwk2/c_hwk2)
==11356==    by 0x4010C2: main (in /home/elena/CodeBlocksProjects/c_hwk2/c_hwk2)
==11356==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==11356==

********* MENU ************
Your collection of 10 unique stocks from stocks.txt is:
AAPL	BRCD	CSCO	GOOG	MIPS	MSFT	NVDA	TDF	VZ	XLNX

   1. Show some number of most recent quotes for a particular stock.
   2. Show portion of stocks + most recent quote between any 2 stock symbols.
   3. Quit.
Enter an option (1, 2, or 3) : BLAH!!

********* MENU ************
Your collection of 10 unique stocks from stocks.txt is:
AAPL	BRCD	CSCO	GOOG	MIPS	MSFT	NVDA	TDF	VZ	XLNX

   1. Show some number of most recent quotes for a particular stock.
   2. Show portion of stocks + most recent quote between any 2 stock symbols.
   3. Quit.
Enter an option (1, 2, or 3) : 1

**See some number of most recent quotes from particular stock**
	Enter the stock name and number of quotes, in the form: STOCK_NAME NUMBER (ie GOOG 3):	XLNX 100

Please select at most the number of quotes recorded (10) in XLNX.

**See some number of most recent quotes from particular stock**
	Enter the stock name and number of quotes, in the form: STOCK_NAME NUMBER (ie GOOG 3):	XLNX 10
XLNX
	93.00
	33.12
	18.75
	26.95
	26.95
	40.75
	33.60
	67.75
	35.69
	24.72

********* MENU ************
Your collection of 10 unique stocks from stocks.txt is:
AAPL	BRCD	CSCO	GOOG	MIPS	MSFT	NVDA	TDF	VZ	XLNX

   1. Show some number of most recent quotes for a particular stock.
   2. Show portion of stocks + most recent quote between any 2 stock symbols.
   3. Quit.
Enter an option (1, 2, or 3) : 1

**See some number of most recent quotes from particular stock**
	Enter the stock name and number of quotes, in the form: STOCK_NAME NUMBER (ie GOOG 3):	BLAH!

Please type in a correct existing stock name (displayed in main menu).

**See some number of most recent quotes from particular stock**
	Enter the stock name and number of quotes, in the form: STOCK_NAME NUMBER (ie GOOG 3):	AAPL 2
AAPL
	184.40
	91.12

********* MENU ************
Your collection of 10 unique stocks from stocks.txt is:
AAPL	BRCD	CSCO	GOOG	MIPS	MSFT	NVDA	TDF	VZ	XLNX

   1. Show some number of most recent quotes for a particular stock.
   2. Show portion of stocks + most recent quote between any 2 stock symbols.
   3. Quit.
Enter an option (1, 2, or 3) : 2

**See stocks between 2 stock symbols along with their most recent quote (ie GOOG VZ)**
***The shortest path will be displayed, forward or backward***
	Enter the range, in the form: STOCK_FROM STOCK_TO:	BLAH!

Please type in a correct existing stock name (displayed in main menu).

**See stocks between 2 stock symbols along with their most recent quote (ie GOOG VZ)**
***The shortest path will be displayed, forward or backward***
	Enter the range, in the form: STOCK_FROM STOCK_TO:	VZ NVDA
VZ (43.51)
TDF (21.92)
NVDA (34.65)

********* MENU ************
Your collection of 10 unique stocks from stocks.txt is:
AAPL	BRCD	CSCO	GOOG	MIPS	MSFT	NVDA	TDF	VZ	XLNX

   1. Show some number of most recent quotes for a particular stock.
   2. Show portion of stocks + most recent quote between any 2 stock symbols.
   3. Quit.
Enter an option (1, 2, or 3) : NVDA XLNX

********* MENU ************
Your collection of 10 unique stocks from stocks.txt is:
AAPL	BRCD	CSCO	GOOG	MIPS	MSFT	NVDA	TDF	VZ	XLNX

   1. Show some number of most recent quotes for a particular stock.
   2. Show portion of stocks + most recent quote between any 2 stock symbols.
   3. Quit.
Enter an option (1, 2, or 3) : 2

**See stocks between 2 stock symbols along with their most recent quote (ie GOOG VZ)**
***The shortest path will be displayed, forward or backward***
	Enter the range, in the form: STOCK_FROM STOCK_TO:	NVDA XLNX
NVDA (34.65)
TDF (21.92)
VZ (43.51)
XLNX (93.00)

********* MENU ************
Your collection of 10 unique stocks from stocks.txt is:
AAPL	BRCD	CSCO	GOOG	MIPS	MSFT	NVDA	TDF	VZ	XLNX

   1. Show some number of most recent quotes for a particular stock.
   2. Show portion of stocks + most recent quote between any 2 stock symbols.
   3. Quit.
Enter an option (1, 2, or 3) : 3
==11356==
==11356== HEAP SUMMARY:
==11356==     in use at exit: 0 bytes in 0 blocks
==11356==   total heap usage: 163 allocs, 163 frees, 3,971 bytes allocated
==11356==
==11356== All heap blocks were freed -- no leaks are possible
==11356==
==11356== For counts of detected and suppressed errors, rerun with: -v
==11356== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
elena@elena-e5250 ~/CodeBlocksProjects/c_hwk2 $

*/
