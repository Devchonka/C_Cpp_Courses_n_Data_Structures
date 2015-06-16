/*********************************************************************************
** CIS 26B                                                            Spring, 2015
** Advanced C
******************
**
** Homework 5: Binary Search Trees and Queues
**********************************************************************************
**  Written By: Menyaylenko, Elena
**
**  Date:               05/30/2015
**  IDE (compiler):     GNU GCC Compiler, Unix OS
**
    Procedure:
    x 1) Read in command line arguments of input and output file names
    x 2) Decide on line and page dimensions per requirement
    x 3) Read in file, lower-casing all letters
    4) Set up BST to take word, freq, and queue pointers
    5) Set up queue to hold page and line numbers
    6)


    Extra: Lazy delete stradegy

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

void get_fnames(char*, char*, int, char**);
void read_file(char*, bstNODE**);
void tokenize_line(char*, bstNODE**); // insert to BST here
char* lowercase(char*);

void queue_driver();
void bst_driver();

//const int WORD_SIZE = 32;
const int LINE_SIZE = 1024; // characters per line
const int PAGE_SIZE = 60; // lines per page

int main(int argc, char** argv)
{
    char fname_in[256]="";
    char fname_out[256]="";
    get_fnames(fname_in, fname_out, argc, argv);
    bstNODE* root = NULL;
    read_file(fname_in, &root);
    //printTreeInorder(root);
    //queue_driver();
    //bst_driver();
    return 0;
}

/**
    Function get_fnames returns by reference the input and output file names,
    depending on user preference from command line.
	Pre:  fname_in, fname_out, argc, argv
	Post: n/a
*/
void get_fnames(char* fname_in, char* fname_out, int argc, char** argv)
{
    char default_fname_in[] = "le_petit_prince.txt";
    char default_fname_out[] = "out.txt";
    switch(argc)
    {
    case 1:
    {
        strcpy(fname_in, default_fname_in);
        strcpy(fname_out, default_fname_out);
        break;
    }
    case 2:
    {
        strcpy(fname_in, argv[1]);
        strcpy(fname_out, default_fname_out);
        break;
    }
    case 3:
    {
        strcpy(fname_in, argv[1]);
        strcpy(fname_out, argv[2]);
        break;
    }
    default:
    {
        fprintf(stderr, "Usage: %s [input_file.txt] [output_file.txt]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    }
}



void read_file(char* fname_in, bstNODE** root)
{
    char line[LINE_SIZE];
    FILE* ifp;
    ifp = fopen(fname_in, "r");
    if(!ifp)
    {
        printf("Error: Cannot open file.\n");
    }
    if(!fgets(line, sizeof(line), ifp))
    {
        fprintf(stderr, "Error: empty input file %s\n", fname_in);
        exit(EXIT_FAILURE);
    }
    while(fgets(line, sizeof(line), ifp))
    {
        tokenize_line(line, root);
    }
    fclose(ifp);
}

void queue_driver()
{
    qNODE *queue = NULL, *rear = NULL;
    qNODE *front;
    qDATA qdata;
    qdata.line =3;
    qdata.page =5;
    enqueue(&queue, &rear, qdata);
    enqueue(&queue, &rear, qdata);
    enqueue(&queue, &rear, qdata);
    front = dequeue(&queue, &rear);
    if(front)
    {
        printf("Front node of queue is %d\n", front->data.page);
        free(front);
    }
    else
    {
        printf("Empty queue!\n");
    }
    front = dequeue(&queue, &rear);
    if(front)
    {
        printf("Front node of queue is %d\n", front->data.page);
        free(front);
    }
    else
    {
        printf("Empty queue!\n");
    }
    front = dequeue(&queue, &rear);
    if(front)
    {
        printf("Front node of queue is %d\n", front->data.page);
        free(front);
    }
    else
    {
        printf("Empty queue!\n");
    }
    front = dequeue(&queue, &rear);
    if(front)
    {
        printf("Front node of queue is %d\n", front->data.page);
        free(front);
    }
    else
    {
        printf("Empty queue!\n");
    }
}
/*
void bst_driver()
{
    bstNODE *root, *ptr;
   int   n = 10, s = 10;

   char r[] = "hi";

   srand(time(NULL));
   root = buildBinaryTree( n );
   printTreeInorder( root );

   while (s--)
   {
       ptr = find(root, r);
       if(ptr)
          printf("%s found: %s\n", r, ptr->bstData.word);
       else
          printf("%s NOT found!\n", r);
   }
   printf( "\n\n" );
}
*/

void tokenize_line(char line[], bstNODE** root) // also insert tokens to bst/queue
{
    bstDATA newTreeData;
    char* word = strtok(line,"\040\t\n,");
    if(word)
    {
        char* new_word = lowercase(word);
        newTreeData.word = new_word;
        insert(root, newTreeData);
    }
    while(word)
    {
        char* new_word = lowercase(word);
        newTreeData.word = new_word;
        insert(root, newTreeData);
        word = strtok(NULL,"\040\t\n,");
    }
}

char* lowercase(char* str)
{
    char* lowered_string  = (char*) malloc((1+strlen(str)) * sizeof(char));
    if(!lowered_string)
    {
        printf("Error: Fatal error in string malloc.\n");
        return NULL;
    }
    int length = strlen(str);
    int i=0;
    for(; i<length; i++)
    {
        lowered_string[i] = tolower(str[i]);
    }
    return lowered_string;
}
