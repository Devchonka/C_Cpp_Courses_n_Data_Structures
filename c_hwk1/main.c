/*********************************************************************************
** CIS 26B													    Spring, 2015
** Advanced C
** Homework 1: Review
**        Arrays, Pointers, Strings, Structures, and Dynamic Allocation of Memory
**
**  Written By: Menyaylenko, Elena
**
**  Date:               04/15/2015
**  IDE (compiler):     GNU GCC Compiler, Unix OS
**
    Procedure:
    1) Obtain the input and output file names
    2) Read file
    3) Create dynamically allocated array of structs containing state/city and temp
    4) Use insertion sort to sort the data by state/city
    5) Write output file, making sure to average same ones
    6) Check memory leak detection using VALGRIND

    To compile code:
        gcc -std=c99  main.c defines.h defines.c -o c_hwk1

    To check memory leaks with Valgrind:
        valgrind --tool=memcheck --leak-check=yes ./c_hwk1
************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "defines.h"

void get_fnames(char*, char*, int, char**);

int main(int argc, char** argv)
{
    char fname_in[256]="";
    char fname_out[256]="";
    int structArray_size = 0;
    LOC_DATA* pStructArray = NULL;
    get_fnames(fname_in, fname_out, argc, argv);
    pStructArray = read_file(fname_in, &structArray_size);
    insertion_sort(pStructArray, structArray_size);
    write_file(fname_out,pStructArray, &structArray_size);
    free_memory(pStructArray, structArray_size);
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


/**
    PROGRAM OUTPUT:
    Upon empty file or with '0' lines:
Error: empty input file in.txt

    Upon regular file testing (with or without empty lines in it):

Arizona,Flagstaff:82.5
Arizona,Phoenix:108.0
Arizona,Tucson:103.0
California,Los Angeles:80.3
California,San Francisco:66.0
California,San Francisco:100.0
Nevada,Reno:108.0
Oregon,Portland:80.5
Oregon,Salem:86.0
Pennsylvania,Philadelphia:88.5

    VALGRIND OUTPUT:
==14384== Memcheck, a memory error detector
==14384== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==14384== Using Valgrind-3.10.0.SVN and LibVEX; rerun with -h for copyright info
==14384== Command: ./c_hwk1
==14384==
==14384==
==14384== HEAP SUMMARY:
==14384==     in use at exit: 0 bytes in 0 blocks
==14384==   total heap usage: 26 allocs, 26 frees, 1,924 bytes allocated
==14384==
==14384== All heap blocks were freed -- no leaks are possible
==14384==
==14384== For counts of detected and suppressed errors, rerun with: -v
==14384== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
*/
