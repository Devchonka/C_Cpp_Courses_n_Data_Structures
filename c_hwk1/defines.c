#include "defines.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/** Read file and return dynamically allocated array of structs
	Pre:  fname_in, pStructArray_size
	Post: LOC_DATA* - array of structs on the heap
*/
LOC_DATA* read_file(char* fname_in, int* pStructArray_size)
{
    LOC_DATA* pStructArray = NULL;
    char line[256];
    FILE* ifp;
    ifp = fopen(fname_in, "r");
    int index = 0;
    if(ifp == NULL)
    {
        fprintf(stderr, "Error opening the input file. %s\n", fname_in);
        exit(EXIT_FAILURE);
    }
    if(fgets(line, sizeof(line), ifp)==NULL || atoi(line) ==0)
    {
        fprintf(stderr, "Error: empty input file %s\n", fname_in);
        exit(EXIT_FAILURE);
    }
    *pStructArray_size = atoi(line);
    pStructArray = malloc(sizeof(LOC_DATA) **pStructArray_size);
    while(fgets(line, sizeof(line), ifp))
    {
        if(line[0] != '\n')
        {
            add_struct(line, pStructArray);
        }
        index++;
    }
    fclose(ifp);
    return pStructArray;
}

/** Adds a struct into the next element in the array every time its called using an incrementing static variable
	Pre:  line, pStructArray
	Post: n/a
*/
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

/** Write to a file with the name provided to user, the average temperatures of non-repeated city/states
	Pre:  fname_out, pStructArray, structArray_size
	Post: bool - whether the writing to the file will be successful
*/
bool write_file(char* fname_out, LOC_DATA* pStructArray, int* structArray_size)
{
    LOC_DATA pAvgArray[*structArray_size];
    int avgArray_size = 0;
    FILE* ofp;
    ofp = fopen(fname_out, "w");
    bool ableToWrite = (ofp);
    if(!ableToWrite)
    {
        fprintf(stderr, "Error opening the output file %s\n", fname_out);
        exit(1);
    }
    avgArray_size = get_avgArray(pStructArray, structArray_size, pAvgArray);
    for(int i =0; i < avgArray_size; i++)
    {
        fprintf(ofp, "%s:%.1lf\n", pAvgArray[i].cityState, pAvgArray[i].temp);
    }
    fclose(ofp);
    return ableToWrite;
}

/** Use insertion sort algorithm to sort an array of structs
	Pre:  pStructArray, structArray_size
	Post: n/a
*/
void insertion_sort(LOC_DATA* pStructArray, int structArray_size)
{
    int i;
    for(i=0; i<structArray_size-1; i++)
    {
        if(strcmp(pStructArray[i+1].cityState, pStructArray[i].cityState)  < 0)
        {
            int j=i+1;
            LOC_DATA tmp = pStructArray[j];
            while(j>0 && (strcmp(pStructArray[j-1].cityState, tmp.cityState) > 0))
            {
                pStructArray[j] = pStructArray[j-1];
                j--;
            }
            pStructArray[j] = tmp;
        }
    }
}

/** Take a non-unique values array and copy each unique value for city/state with the average temp for those values
	Pre:  orig_array (sorted), orig_size, avg_array
	Post: int - number of unique values in original array
*/
int get_avgArray(LOC_DATA* orig_array, int* orig_size, LOC_DATA* avg_array)
{
    int avgArray_index =0;
    double avg_temp = 0.0;
    for(int i =0; i<*orig_size-1; i++)
    {
        double sum = orig_array[i].temp;
        double num_sameOnes = 1.0;
        while(strcmp(orig_array[i].cityState, orig_array[i+1].cityState) == 0)
        {
            sum += orig_array[i+1].temp;
            num_sameOnes+=1.0;
            i++;
        }
        avg_temp = sum / num_sameOnes;
        avg_array[avgArray_index].cityState = orig_array[i-1].cityState;
        avg_array[avgArray_index++].temp = avg_temp;
    }
    return avgArray_index;
}

/** Frees memory of the string allocated by each struct, and then the entire array
	Pre:  pStructArray, structArray_size
	Post: n/a
*/
void free_memory(LOC_DATA* pStructArray, int structArray_size)
{
    for(int i =0; i<structArray_size; i++)
    {
        free(pStructArray[i].cityState);
    }
    free(pStructArray);
}
