/**
record.c - file that contains all the source code for the record.h file.
*/
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
    {
        printf("Please type in exactly 4 words: studentID FirstName LastName Amount");
    }
    return valid;
}

/*
 Function to ensure only allowed characters are validated.
*/
bool has_only_allowed(char* string, char* allowed)
{
    return !(strspn(string, allowed)<strlen(string));
}

/*
Function that ensures that teh name contains only alphabetic characters.
*/
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
        printf("\n\tError: Student names must be typed using English alphabet letters only.\n");
    }
    return valid;
}

/*
Function to ensure student ID is exactly 4 letters.
*/
bool validate_studentID(char* id)
{
    bool valid = (strlen(id)==4);
    if(valid)
    {
        valid = has_only_allowed(id, "0123456789");
    }
    if(!valid)
    {
        printf("\n\tError: Student IDs must be typed using 4 digits only.\n");
    }
    return valid;
}

/*
Function to ensure that the dollar amount is valid to 2 decimal places, and contains digits only.
*/
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
        printf("\n\tError: Financial aid amount must be $10.00-99999.99 (2 digits after decimal point).\n");
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
    long address = key * 2654435761;
    return address% hashTable_size;
}

/********************************************************
   Create an empty hash file
*/
FILE* create_hash_file(char* filename)
{
    FILE* fp;
    RECORD hashtable[TABSIZE][BUCKETSIZE] = {{""}};
    if((fp = fopen(filename, "w+b")) == NULL)
    {
        printf("\n\tError: Could not open file %s.\n", filename);
        exit(1);
    }
    // check for write errors just to be safe.
    if(fwrite(&hashtable[0][0], sizeof(RECORD), TABSIZE * BUCKETSIZE, fp) < TABSIZE)
    {
        printf("Hash table could not be created. Abort!\n");
        exit(2);
    }
    rewind(fp);
    return fp;
}

/*
Function to make a string into an upper characters string.
*/
void make_toUpper(char str[][21])
{
    int i=0;
    while(*str[i])
    {
        *str[i] = toupper(*str[i]);
        i++;
    }
}

/******************************************************
   Hashing to Disk: Insert
*/
bool insert_record(RECORD rec, FILE* fp)
{
    RECORD detect;
    long address = hash_func(rec.studentId, TABSIZE);
    make_toUpper(&rec.firstname);
    make_toUpper(&rec.lastname);
    int i;
    // go to beginning of hash bucket
    if(fseek(fp, address * BUCKETSIZE * sizeof(RECORD), SEEK_SET) != 0)
    {
        printf("\n\tError: Fatal seek error! Abort!\n");
        exit(4);
    }
    // find first available slot in the bucket.
    for(i = 0; i < BUCKETSIZE; i++)
    {
        fread(&detect, sizeof(RECORD), 1, fp);
        if(*detect.firstname == '\0')  // available slot
        {
            fseek(fp, -1L * sizeof(RECORD), SEEK_CUR);
            fwrite(&rec, sizeof(RECORD), 1, fp);
            printf("Record: %d :added to bucket %ld.\n", rec.studentId, address);
            return true; // nothing left to do
        }
    }
    printf("\n\tError: Destined hash bucket %ld is full, entry %d not inserted!\n", address, rec.studentId);
    return false;
}

/*
Function to search for and delete a record already given its address.
*/
bool delete_record(unsigned studentId_2_delete, long address, FILE* fp)
{
    RECORD detect;
    int i;
    // go to beginning of hash bucket
    if(fseek(fp, address * BUCKETSIZE * sizeof(RECORD), SEEK_SET) != 0)
    {
        printf("\n\tError: Fatal seek error! Abort!\n");
        exit(4);
    }
    // find first available slot in the bucket.
    for(i = 0; i < BUCKETSIZE; i++)
    {
        fread(&detect, sizeof(RECORD), 1, fp);
        if(detect.studentId == studentId_2_delete)  // right one to delete
        {
            detect.studentId=0;
            detect.firstname[0] ='\0';
            detect.lastname[0] = '\0';
            detect.amount = 0.00;
            fseek(fp, -1L * sizeof(RECORD), SEEK_CUR);
            fwrite(&detect, sizeof(RECORD), 1, fp);
            printf("Record: %d :deleted from bucket %ld.\n", studentId_2_delete, address);
            return true; // nothing left to do
        }
    }
    printf("\n\tError: Destined hash bucket %ld does not have the searched record!\n", address);
    return false;
}

/*
Function to print just one record given a pointer to the record.
*/
void print_rec_at_address(RECORD* rec)
{
    printf("%d %s %s %.2lf\n", rec->studentId, rec->firstname, rec->lastname, rec->amount);
}
/******************************************************
   Hashing to Disk: Search. The function returns a true is found, false otherwise. The function returns a pointer
   to the found record and its address.
*/
bool search_record(RECORD* rec, long* address, FILE* fp)
{
    *address = hash_func(rec->studentId, TABSIZE);
    RECORD detect;
    int i;
    if(fseek(fp, *address * BUCKETSIZE * sizeof(RECORD), SEEK_SET) != 0)
    {
        printf("\n\tError: Fatal seek error! Abort");
        exit(4);
    }
    // find first available slot in bucket
    for(i = 0; i < BUCKETSIZE; i++)
    {
        fread(&detect, sizeof(RECORD), 1, fp);
        if(rec->studentId == detect.studentId)  // found it!
        {
            printf("\t%d found \n\tat hash bucket %ld.\n", detect.studentId, *address);
            return true; // nothing left to do
        }
    }
    printf("Records with key: %d : not found.\n", rec->studentId);
    return false;
}
/*
Function to print all records in the file.
*/
void print_all_records(FILE* fp)
{
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);
    int i;
    RECORD detect;
    while(ftell(fp)!=file_size)
    {
        fread(&detect, sizeof(RECORD), 1, fp);
        if(detect.studentId != 0)
        {
            print_rec_at_address(&detect);
        }
    }
}
