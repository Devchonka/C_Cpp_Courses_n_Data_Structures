/*********************************************************************************
** CIS 26B                                                            Spring, 2015
** Advanced C
******************
**
** Homework 5: Binary Search Trees and Queues
**********************************************************************************
**  Written By: Menyaylenko, Elena
**
**  Date:               06/16/2015
**  IDE (compiler):     GNU GCC Compiler, Unix OS
**

    To compile code:
        gcc -std=c99  *.h *.c -o c_hwk5
    To check memory leaks with Valgrind: - no dynamic allocations in this code
        valgrind --tool=memcheck --leak-check=yes ./c_hwk5

    To use gdb debugger:
        cc -g *.c *.h -o c_hwk5
        gdb c_hwk5
        break line_number OR break [file_name]:line_number OR break [file_name]:func_name
        run [args] // if program requires command line args
        print variable_name
        c //continue
        s // step
************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "BST.h"
#include "queue.h"

void get_fnames(char**, char**, int, char**);
void read_file(char*, bstNODE**);
void write_file(char*, bstNODE*);
void tokenize_line(char*, bstNODE**); // insert to BST here
char* lowercase(char*);
void delete_trailingJunk(char[]);
char* get_timeStamp();
char* allocateString(char*);

const int LINE_SIZE = 1024; // characters per line
const int PAGE_SIZE = 60; // lines per page

/**
    Function main takes in command line arguments and prints out the results.
    It puts a time stamp. At the end of execution, it frees dynamically allocated memory.
*/
int main(int argc, char** argv)
{
    // Get file names from user
    char* fname_in = NULL;
    char* fname_out = NULL;
    get_fnames(&fname_in, &fname_out, argc, argv);
    // Build the BST with leafs containing queues
    bstNODE* root = NULL;
    read_file(fname_in, &root);
    //printTreeInorder(root);
    write_file(fname_out, root);
    root = freeTree(root);
    free(fname_in);
    free(fname_out);
    return 0;
}

/**
    Function get_timeStamp modifies the value of the char buffer
*/
char* get_timeStamp()
{
    struct tm *timeptr;
    time_t timeval;
    char time_buffer[80];
    time(&timeval);
    timeptr = localtime(&timeval);
    strftime(time_buffer, 80, "%c\n", timeptr);
    char* return_string = allocateString(time_buffer);
    return return_string;
}

/** Create a dynamically allocated string
	Pre:  tempString
	Post: string - dynamically allocated
*/
char* allocateString(char* tempString)
{
    char* string;
    int   stringSize;
    stringSize = strlen(tempString) + 1;
    string = calloc(stringSize, sizeof(char));
    if(string == NULL)
    {
        printf("Error: not enough memory for string allocation of state/city.\a\n");
        exit(1);
    }
    strcpy(string, tempString);
    return string;
}

/**
    Function get_fnames returns by reference the input and output file names,
    depending on user preference from command line.
	Pre:  fname_in, fname_out, argc, argv
	Post: n/a
*/
void get_fnames(char** fname_in, char** fname_out, int argc, char** argv)
{
    char default_fname_in[] = "le_petit_prince.txt";
    char default_fname_out[] = "out.txt";
    switch(argc)
    {
    case 1: // no args provided: use defaults
    {
        *fname_in = allocateString(default_fname_in);
        *fname_out = allocateString(default_fname_out);
        break;
    }
    case 2: // only input file provided, so output is default file name
    {
        *fname_in = allocateString(argv[1]);
        *fname_out = allocateString(default_fname_out);
        //strcpy(fname_in, argv[1]);
        //strcpy(fname_out, default_fname_out);
        break;
    }
    case 3: // both input and output file names provided
    {
        *fname_in = allocateString(argv[1]);
        *fname_out = allocateString(argv[2]);
        break;
    }
    default:
    {
        fprintf(stderr, "Usage: %s [input_file.txt] [output_file.txt]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    }
}

/**
    Function read_file reads an input file, and passes the line into a function which will tokenize
    the line, in order to fill out the tree.
*/
void read_file(char* fname_in, bstNODE** root)
{
    char line[LINE_SIZE];
    FILE* ifp;
    ifp = fopen(fname_in, "r");
    if(!ifp)
    {
        printf("Error: Cannot open input file %s.\n", fname_in);
        exit(1);
    }
    while(fgets(line, sizeof(line), ifp))
    {
        if(line[0] != '\n') // single newline will go through
        {
            line[strlen(line)-1] = '\0'; // get rid of newline
        }
        tokenize_line(line, root);
    }
    fclose(ifp);
}

/**
    Function used to write the lexically parsed file to a new file named by the user (or default).
*/
void write_file(char* fname_out, bstNODE* root)
{
    FILE* ofp;
    ofp = fopen(fname_out, "w+a");
    if(!ofp)
    {
        printf("Error: Cannot open output file %s.\n", fname_out);
        exit(1);
    }

    char* time = get_timeStamp();
    fprintf(ofp, "\nReport made at: %s\n", time);
    printTreeInorder(root, ofp);

    fclose(ofp);
    free(time);
}

/**
    Function tokenize_line will break a line into words, in order to pass them to a tree building function for the BST.
*/
void tokenize_line(char line[], bstNODE** root) // also insert tokens to bst/queues
{
    static int line_num =0;
    static int page_num =0;
    char* word = strtok(line,"\040\t\n,");
    if(word) // first word in the line
    {
        delete_trailingJunk(word);
        char* new_word = lowercase(word);
        insert_bstNode(root, new_word, line_num, page_num);
    }
    while(word) // remaining words in the line
    {
        word = strtok(NULL,"\040\t\n,");
        if(word)
        {
            delete_trailingJunk(word);
            char* new_word = lowercase(word);
            insert_bstNode(root, new_word, line_num, page_num);
        }
    }
    line_num++;
    page_num = line_num / LINE_SIZE;
}

/**
    Function lowercase lowers all the letters in a string passed to it, and returns a pointer to a dynamically
    allocated array of characters for the minimum length of a string.
*/
char* lowercase(char str[]) // also dynamically allocates memory for new string
{
    char* lowered_string ="";
    if(str)
    {
        int length = strlen(str);
        lowered_string  = (char*) malloc((1+length) * sizeof(char));
        if(!lowered_string)
        {
            printf("Error: Fatal error in string malloc.\n");
            return NULL;
        }
        int i=0;
        for(; i<length; i++)
        {
            lowered_string[i] = tolower(str[i]);
        }
        lowered_string[length] = '\0';
    }
    return lowered_string;
}

/**
    Function to get rid of trailing unneeded chars. Currently implemented for dot.
*/

void delete_trailingJunk(char word[])
{
    char un_allowedLetters[] = ".?\",')";
/*
    while (strcspn(word, un_allowedLetters)==0)
    {
        printf("%d\n", strcspn(word, un_allowedLetters));
        strcpy(word, &word[1]);
    }
*/

    while(word[strlen(word)-1] == '.' || word[strlen(word)-1] == '?' || word[strlen(word)-1] == '"' || word[0] == ')')
    {
        word[strlen(word)-1] = '\0';
    }

    while(word[0] == '.' || word[0] == '!' || word[0] == '"' || word[0] == '\'' || word[0] == '-' || word[0] == '(')
    {
        strcpy(word, &word[1]);
    }
}

/**
OUTPUT:

*/
