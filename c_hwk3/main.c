/*********************************************************************************
** CIS 26B                                                            Spring, 2015
** Advanced C
******************
**
** Homework 2: Financial Aid Data Base - Hashing to Disk and Advanced String Handling.
** Write a program that allows deletions, additions, displays of database of records.
**********************************************************************************
**  Written By: Menyaylenko, Elena
**
**  Date:               05/14/2015
**  IDE (compiler):     GNU GCC Compiler, Unix OS
**
    Procedure:
    x 1) Create struct record instance
    x 2) Read in file to load some records
    3) Create menu for user to allow 4 options
    4) Create menu keyboard validation for user
     - names: only have letters
     - student id: exactly 4 digits
     - amount needs a decimal point number between 10-99999.99
    5) Make sure all string functions are strtok, strtod, etc
    6)



    x) Check memory leak detection using VALGRIND

    To compile code:
        gcc -std=c99  *.c *.h -o c_hwk3
    To check memory leaks with Valgrind:
        valgrind --tool=memcheck --leak-check=yes ./c_hwk3
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "record.h"

void read_file(const char*);
char get_user_choice();
bool validate_new_record();



const unsigned int LINE_SIZE = 512;
const char* FNAME = "fin_aid.txt";

int main(int argc, char** argv)
{
    read_file(FNAME);

    return 0;
}

/**
Function read_file. Reads a valid file and ..
*/
void read_file(const char* fname_in)
{
    char line[LINE_SIZE];
    FILE* ifp;
    ifp = fopen(fname_in, "r");
    int index = 0;
    if(fgets(line, LINE_SIZE, ifp)==NULL)
    {
        fprintf(stderr, "Error: empty input file %s\n", fname_in);
        exit(EXIT_FAILURE);
    }
    char temp_Lname[21], temp_Fname[21];
    double temp_amount;
    unsigned int temp_sId;

    while(fgets(line, LINE_SIZE, ifp))
    {
        if(line[0] != '\n')
        {
            sscanf(line, "%d %20[^ ]%*c %20[^ ]%*c %lf", &temp_sId, temp_Lname, temp_Fname, &temp_amount);

        }
        index++;
    }
    fclose(ifp);
}

/**********************************
**     MENU / VALIDATION FUNCTIONS
***********************************/

/**
Function user_menu. Prompts the user to ...
*/
void user_menu()
{
    char temp_Lname[21], temp_Fname[21];
    double temp_amount;
    unsigned int temp_sId;

    char choice;
    do
    {
        choice = get_user_choice();
        switch(choice)
        {
        case '1':
        {
                printf("*****Display current records in database.*****\n");
                // print whats hashed to disk
            break;
        }
        case '2':
        {
            char user_input[LINE_SIZE];
            do
            {
                putchar('\n');
                printf("****Add new record entry into database.****\n");

                fgets(user_input, LINE_SIZE, stdin);
                //parse line using str functions
            }
            while(!(validate_new_record()));
            // add new record
            break;
        }
        case '3':
        {
            char user_input[LINE_SIZE];
            do
            {
                putchar('\n');
                printf("****Delete record entry from database.****\n");

                fgets(user_input, LINE_SIZE, stdin);
                //parse line using str functions
            }
            while(!(validate_new_record())); // should be validate just 1 thing..
            // delete record
            break;
        }
        case '4':
            break;
        default:
        {
            printf("Error in switch statement in user menu.\n");
            exit(EXIT_FAILURE);
        }
        }
    }
    while(choice!='3');
}

/**
 Function get_user_choice.
*/
char get_user_choice()
{
    char choice, line[LINE_SIZE];
    do
    {
        putchar('\n');
        printf("********* MENU ************\n");
        putchar('\n');
        printf("   1. Display current records in database.\n");
        printf("   2. Add new record entry into database.\n");
        printf("   3. Delete record from database.\n");
        printf("   4. Quit.\n");
        printf("Enter an option (1, 2, 3, or 4) : ");
        fgets(line, LINE_SIZE, stdin);
        choice = (strlen(line)>2)? '0' : line[0];
    }
    while(choice<'1' || choice>'4');
    return choice;
}

/**
Function validate_new_record.
*/

bool validate_new_record()
{
    //
    return true;
}
