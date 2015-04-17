#ifndef DEFINES_H
#define DEFINES_H

#include <stdbool.h>

typedef struct{
	char*  cityState;
	double temp;
}LOC_DATA;


LOC_DATA* read_file(char*, int*);
char* allocateString(char*);
void add_struct(char*, LOC_DATA*);
void insertion_sort(LOC_DATA*, int);
bool write_file(char*, LOC_DATA*, int*);
bool free_memory(LOC_DATA*, int);


#endif
