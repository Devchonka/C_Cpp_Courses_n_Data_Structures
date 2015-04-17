#ifndef DEFINES_H
#define DEFINES_H

#include <stdbool.h>

typedef struct{
	char*  cityState;
	double temp;
}LOC_DATA;


int read_file(char*, LOC_DATA*);
char* allocateString(char*);
void add_struct(char*, LOC_DATA*);
bool write_file(char*);


#endif
