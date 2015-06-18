/**
    Function to get ints from user
    Output file name comes from user from terminal.
    Write ints into bin file in reverse order of entry.
    Only enter valid ints, reject and tell user otherwise.
    Function must be recursive and accept 1 argument, FILE* of file to be created.
    Assume that file can be opened/closed outside function.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
void recordReverse(FILE*);

int main(int argc, char* argv[])
{
    // get user numbers and write to file
    FILE* ofp;
    if(!(ofp=fopen(argv[1], "wb")))
    {
        printf("Error opening file %s\n", argv[1]);
        exit(1);
    }
    recordReverse(ofp);
    fclose(ofp);

    // now to read what is recorded..
    FILE* ifp;
    ifp=fopen(argv[1], "rb");
    fseek(ifp, 0, SEEK_END); // seek to end of file
    int num_entries = ftell(ifp)/sizeof(int); // get current file pointer
    fseek(ifp, 0, SEEK_SET); // seek back to beginning of file
    int input[num_entries];
    fread(input, sizeof(int), num_entries, ifp);

    printf("\nNumber of entries: %d\n", num_entries);
    for(int i=0; i<num_entries; i++)
    {
        printf("%d ", input[i]);
    }
    putchar('\n');
    fclose(ifp);
    return 0;
}

void recordReverse(FILE* ofp)
{
    char line[256];
    char *token, *endp;
    long num;
    int errflag;
    do
    {
        errflag =0;
        errno = 0;
        printf("Enter an int or quit: ");
        fgets(line, sizeof(line), stdin);
        token = strtok(line,"\040\t\n");
        if(!token)
        {
            continue;
        }
        if(strcmp(token, "quit") ==0)
        {
            return;
        }
        num = strtol(token, &endp, 10);
        if(errno==ERANGE)
        {
            errflag =1;
            printf("Error: number is too big.\n");
            continue;
        }
        if(*endp != '\0')
        {
            errflag = 1;
            printf(("Bad int.\n"));
            continue;
        }
    }
    while(!token|| errflag);
    recordReverse(ofp);
    fwrite(&num, sizeof(int), 1, ofp);
}
