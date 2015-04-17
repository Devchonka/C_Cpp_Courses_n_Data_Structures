/*********************************************************************************
** CIS 26B													    Spring, 2015
** Advanced C
** Homework 1: Review
**        Arrays, Pointers, Strings, Structures, and Dynamic Allocation of Memory
**********************************************************************************

   Calculate Average High Temperatures ...

   Save the output as a comment at the end of the program!
**********************************************************
**
**  Written By: Menyaylenko, Elena
**
**  Date:               04/15/2015
**  IDE (compiler):     CodeBlocks 13.12 (GNU GCC Compiler), Unix OS
***************************************************************************/

/**
    Procedure:
    x 1) Obtain the input and output file names
    x 2) Read file
    x 3) Create dynamically allocated array of structs containing state/city and temp
    4) Use insertion sort to sort the data by state/city
    5) Write output file, making sure to average same ones
    6) Check memory leak detection using VALGRIND
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "defines.h"



#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

void get_fnames(char*, char*, int, char**);

int main(int argc, char** argv)
{
    char fname_in[256]="";
    char fname_out[256]="";
    int x =0;
    int* structArray_size = &x;
    /* Create a pointer to a future dynamically allocated array of structs   */
    LOC_DATA* pStructArray = NULL;

    get_fnames(fname_in, fname_out, argc, argv);

    pStructArray = read_file(fname_in, structArray_size);

    insertion_sort(pStructArray, *structArray_size);

    write_file(fname_out,pStructArray, structArray_size);

    free_memory(pStructArray, *structArray_size);

#ifdef _MSC_VER
    printf(_CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");
#endif
    return 0;
}


/**
    Function get_fnames returns by reference the input and output file names,
    depending on user preference from command line.
*/
void get_fnames(char* fname_in, char* fname_out, int argc, char** argv)
{
    char default_fname_in[] = "in.txt";
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
