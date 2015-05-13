#include "record.h"

/*****
VALIDATION RECORD FUNCTIONS
******/

/**
Function get_rec_from_valid_line returns a RECORD struct from an already validated line.
*/
RECORD get_rec_from_valid_line(char line[])
{
    RECORD rec;
    rec.studentId = atoi(strtok(line,"\040\t"));
    strcpy(rec.firstname, strtok(NULL,"\040\t"));
    strcpy(rec.lastname, strtok(NULL,"\040\t"));
    rec.amount = atof(strtok(NULL,"\040\t"));

    return rec;
}


/**
Function validate_new_record. Takes in a line, breaks it down to tokens, and if there are exactly 4 entries, it
sends off each bit to be validated individually. It returns a true/false value of whether each token passed.
*/

bool validate_new_record(char* record_line)
{
    bool valid = false;
    char* tokenArray[21];
    int counter =0;
    for(char* p = strtok(record_line,"\040\t"); p != NULL; p = strtok(NULL, " "))
    {
        tokenArray[counter++] = p;
    }
    if(counter==4)
    {
        bool validArray[4];
        validArray[0] = validate_studentID(tokenArray[0]);
        validArray[1] = validate_name(tokenArray[1]);
        validArray[2] = validate_name(tokenArray[2]);
        validArray[3] = validate_amount(tokenArray[3]);
        valid = (validArray[0] && validArray[1] && validArray[2] && validArray[3]);
    }
    else
        printf("Please type in exactly 4 words: studentID FirstName LastName Amount");
    return valid;
}

bool has_only_allowed(char* string, char* allowed)
{
    return !(strspn(string, allowed)<strlen(string));
}

bool validate_name(char* name)
{
    bool valid = strcmp(name, " ");
    char allowedLetters[] = "ABCDEFGHIJKLMNOPQRTSUVWXYZ\
                        abcdefghijklmnopqrstuvwxyz";
    if(valid)
    {
        valid = has_only_allowed(name, allowedLetters);
    }
    if(!valid)
    {
        printf("Error: Student names must be typed using English alphabet letters only.\n");
    }
    return valid;
}

bool validate_studentID(char* id)
{
    bool valid = (strlen(id)==4);
    if(valid)
    {
        valid = has_only_allowed(id, "0123456789");
    }
    if(!valid)
    {
        printf("Error: Student IDs must be typed using 4 digits only.\n");
    }
    return valid;
}

bool validate_amount(char* amount)
{
    bool valid = has_only_allowed(amount, "0123456789.");
    //check decimal point
    if(valid)
    {
        char* pDecimal = strrchr(amount,'.'); // point to decimal point
        valid = (pDecimal!= NULL && (strlen(pDecimal) == 3)); // 2 digits after decimal point
    }
    if(valid)
    {
        valid = (atof(amount)>=10.0 && atof(amount) <= 99999.99);
    }
    if(!valid)
    {
        printf("Error: Financial aid amount must be $10.00-99999.99 (2 digits after decimal point).\n");
    }
    return valid;
}

/*********
HASHING TO DISK RECORD FUNCTIONS
*********/

/*******************************************************
   Hash formula is the same as used in Chapter 3
*/
long hash_func(int key, int hashTable_size)
{
    long address = 0;
    address += key * key * key;
    return address % hashTable_size;
}

/********************************************************
   Create an empty hash file
*/
FILE* create_hash_file(char* filename)
{
    FILE* fp;
    RECORD hashtable[TABSIZE][BUCKETSIZE] = {""};
    RECORD overflow[OFLOWSIZE] = {""};
    if((fp = fopen(filename, "w+b")) == NULL)
    {
        printf("Error: Could not open file %s.\n", filename);
        exit(1);
    }
    // check for write errors just to be safe.
    if(fwrite(&hashtable[0][0], sizeof(RECORD), TABSIZE * BUCKETSIZE, fp) < TABSIZE)
    {
        printf("Hash table could not be created. Abort!\n");
        exit(2);
    }
    if(fwrite(overflow, sizeof(RECORD), OFLOWSIZE, fp) < OFLOWSIZE)
    {
        printf("Could not create overflow area. Abort!\n");
        exit(3);
    }
    rewind(fp);
    return fp;
}

/******************************************************
   Hashing to Disk: Insert
*/
void insert_record(RECORD rec, FILE* fp)
{
    RECORD detect;
    long address = hash_func(rec.studentId, TABSIZE);
    int i;
    // go to beginning of hash bucket
    if(fseek(fp, address * BUCKETSIZE * sizeof(RECORD), SEEK_SET) != 0)
    {
        printf("Fatal seek error! Abort!\n");
        exit(4);
    }
    // find first available slot in the bucket.
    for(i = 0; i < BUCKETSIZE; i++)
    {
        fread(&detect, sizeof(RECORD), 1, fp);
        if(detect.studentId == '\0')  // available slot
        {
            fseek(fp, -1L * sizeof(RECORD), SEEK_CUR);
            fwrite(&rec, sizeof(RECORD), 1, fp);
            printf("Record: %s :added to bucket %ld.\n", rec.studentId, address);
            return; // nothing left to do
        }
    }
    // bucket full: insert into the overflow area
    fseek(fp, TABSIZE * BUCKETSIZE * sizeof(RECORD), SEEK_SET);
    for(i = 0; i < OFLOWSIZE; i++)
    {
        fread(&detect, sizeof(RECORD), 1, fp);
        if(detect.studentId == '\0')  // available slot
        {
            fseek(fp, -1L * sizeof(RECORD), SEEK_CUR);
            fwrite(&rec, sizeof(RECORD), 1, fp);
            printf("Record: %s : added to the overflow slot %d.\n", rec.studentId, i);
            return; // nothing left to do
        }
    }
    // item not inserted!
    printf("Hash table overflow! Abort!\n");
    exit(5);
}

/******************************************************
   Hashing to Disk: Search

void search_record(char *key, long address, FILE *fp)
{
    RECORD detect, temp;
    int i;

    if (fseek(fp, address * BUCKETSIZE * sizeof (RECORD), SEEK_SET) != 0)
    {
        printf("Fatal seek error! Abort");
        exit(4);
    }
    // find first available slot in bucket
    for (i = 0; i < BUCKETSIZE; i++)
    {
        fread(&detect, sizeof (RECORD), 1, fp);
        if (strcmp(detect.key, key) == 0) // found it!
        {
            printf("\t%s found \n\tat hash bucket %ld.\n", key, address);
            printf("\tRandom number is %d\n", detect.num);
            return; // nothing left to do
        }
    }
    // check the overflow area
    fseek(fp, TABSIZE * BUCKETSIZE * sizeof (RECORD), SEEK_SET);
    for (i = 0; i < OFLOWSIZE; i++)
    {
        fread(&detect, sizeof (RECORD), 1, fp);
        if (strcmp(detect.key, key) == 0) // found it!
        {
            printf("\t%s found in overflow area.\n", key);
            printf("\tRandom number is %d\n", detect.num);
            return; // nothing left to do
        }
    }
    // not found
    printf("Recors with key: %s : not found.\n", key);
    return;
}
*/
