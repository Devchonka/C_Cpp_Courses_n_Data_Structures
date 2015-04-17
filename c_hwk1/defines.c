#include "defines.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

LOC_DATA* read_file(char* fname_in, int* pStructArray_size)
{
    LOC_DATA* pStructArray = NULL;
    char line[256];
    FILE* ifp;
    ifp = fopen(fname_in, "r");
    int index = 0;
    if(ifp == NULL)
    {
        fprintf(stderr, "Error opening the input file %s\n", fname_in);
        exit(1);
    }
    fgets(line, sizeof(line), ifp);
    *pStructArray_size = atoi(line);
    pStructArray = malloc(sizeof(LOC_DATA) **pStructArray_size);
    while(fgets(line, sizeof(line), ifp) && line[0] != '\n')
    {
        add_struct(line, pStructArray);
        index++;
    }
    fclose(ifp);
    return pStructArray;
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
    struct_index++;
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


bool write_file(char* fname_out, LOC_DATA* pStructArray, int* structArray_size)
{
    FILE* ofp;
    ofp = fopen(fname_out, "w");
    if(ofp == NULL)
    {
        fprintf(stderr, "Error opening the output file %s\n", fname_out);
        exit(1);
    }
    for(int i =0; i < *structArray_size; i++)
    {
        fprintf(ofp, "%s:%.1lf\n", pStructArray[i].cityState, pStructArray[i].temp);
    }
    fclose(ofp);
    return true;
}

void insertion_sort(LOC_DATA* pStructArray, int structArray_size)
{
    printf("%d\n", structArray_size);
}

bool free_memory(LOC_DATA* pStructArray, int structArray_size)
{
    for(int i =0; i<structArray_size; i++)
    {
        free(pStructArray[i].cityState);
    }
    free(pStructArray);
}
