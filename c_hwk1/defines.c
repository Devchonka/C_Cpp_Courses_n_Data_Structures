#include "defines.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int read_file(char* fname_in, LOC_DATA* pStructArray)
{
    char line[256];
    int num_lines =0;
    FILE* ifp;
    ifp = fopen(fname_in, "r");
    if(ifp == NULL)
    {
        fprintf(stderr, "Error opening the input file %s\n", fname_in);
        exit(1);
    }
    fgets(line, sizeof(line), ifp);
    num_lines = atoi(line);
    pStructArray = malloc(sizeof(LOC_DATA) * num_lines);
    while(fgets(line, sizeof(line), ifp) && line[0] != '\n')
    {
        add_struct(line, pStructArray);
    }
    fclose(ifp);
    return num_lines;
}

void add_struct(char* line, LOC_DATA* pStructArray)
{
    static int struct_index = 0;
    char temp_location[100];
    char* heap_string;
    double heap_temp;

    sscanf(line, "%99[^:]%*c%lf", temp_location, &heap_temp);

    heap_string = allocateString(temp_location);

    pStructArray[struct_index].cityState = heap_string;
    pStructArray[struct_index].temp = heap_temp;
}


/* Create a dynamically allocated string
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


bool write_file(char* fname_out)
{
    FILE* ofp;
    ofp = fopen(fname_out, "w");
    if(ofp == NULL)
    {
        fprintf(stderr, "Error opening the output file %s\n", fname_out);
        exit(1);
    }
    fclose(ofp);
    return true;
}
