#ifndef DEFINES_H
#define DEFINES_H

#include <stdbool.h>

/**
    Struct that holds the city/state and temperature combinations given by the input file
*/
typedef struct
{
    char*  cityState;
    double temp;
} LOC_DATA;

/**
    Function definitions in defines.c
*/
LOC_DATA* read_file(char*, int*);
char* allocateString(char*);
void add_struct(char*, LOC_DATA*);
void insertion_sort(LOC_DATA*, int);
int get_avgArray(LOC_DATA*, int*, LOC_DATA*);
bool write_file(char*, LOC_DATA*, int*);
void free_memory(LOC_DATA*, int);
#endif
