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
    3) Create menu for user to allow 5 options (display all, quit)
        - insert
        - delete
        - find and display
    x 4) Create menu keyboard validation for user
     - names: only have letters
     - student id: exactly 4 digits
     - amount needs a decimal point number between 10-99999.99
    x 5) Make sure all string functions are strtok, strtod, etc
    x 6) Make sure arguments come from command line
    7) Create binary file

    8) Check memory leak detection using VALGRIND

    To compile code:
        gcc -std=c99  *.c *.h -o c_hwk3
    To check memory leaks with Valgrind:
        valgrind --tool=memcheck --leak-check=yes ./c_hwk3
************************************************************************/

#include "record.h"

char* get_fname(char**);
void read_file(const char*);
void user_menu(FILE*);
char get_user_choice();


const unsigned int LINE_SIZE = 512;
char* FNAME_BIN = "records.dat";

int main(int argc, char* argv[])
{

    char* fname = get_fname(argv);
    read_file(fname);

    FILE* fp = create_hash_file(FNAME_BIN);
    user_menu(fp);


/*
    /* // RECORD LINE VALIDATION
    char record[] = "5673 HALL MARC 93.13";
    printf("%d\n",validate_new_record(record));
    //printf("%d\n",validate_name("54"));
    //printf("%d\n",validate_studentID("hhhh"));
    //printf("%d\n",validate_amount("10.00"));*/
    fclose(fp);
    return 0;
}

/**
Function get_fname. Returns filename inputted from command line, if the right number of arguments was put in,
and if the file can be opened in read mode.
*/
char* get_fname(char* argv[])
{
    if(!argv[1] || argv[2])
    {
        printf("Error: Please run the program with 1 argument (ie input_file.txt)\n");
        exit(1);
    }
    FILE* file = fopen(argv[1], "r");
    if(file == 0)
    {
        printf("Error: Input file cannot be opened.\n");
        exit(1);
    }
    fclose(file);
    return argv[1];
}

/**
Function read_file. Reads a valid file and adds records into the hash.
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
            sscanf(line, "%u %20[^ ]%*c %20[^ ]%*c %lf", &temp_sId, temp_Lname, temp_Fname, &temp_amount);
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
void user_menu(FILE* fp)
{
    char choice;
    do
    {
        choice = get_user_choice();
        switch(choice)
        {
        case '1':
        {
            putchar('\n');
            printf("*****Display all current records in database.*****\n");
            // print whats hashed to disk
            break;
        }
        case '2':
        {
            char user_input_record[LINE_SIZE], temp_input[LINE_SIZE];

            do
            {

                putchar('\n');
                printf("\n****Add new record entry into database.****\n");
                printf("Correct format: studentId FirstName LastName FinancialAid\n");
                printf("\nAdd new record in form similar to (6745 SMITH ANNA 7769.87): ");
                if(!fgets(user_input_record, LINE_SIZE, stdin))
                {
                    printf("Error: Error getting line from user input.\n");
                }
                user_input_record[strlen(user_input_record)-1] = '\0'; // get rid of newline
                strcpy(temp_input, user_input_record);
            }
            while(!(validate_new_record(temp_input)));

            // insert new record
            RECORD rec = get_rec_from_valid_line(user_input_record);

            insert_record(rec, fp);

            break;
        }
        case '3':
        {
            char user_input[LINE_SIZE];
            do
            {
                putchar('\n');
                printf("****Delete record entry from database.****\n");
                printf("Enter student ID whose record you would like deleted: ");
                if(!fgets(user_input, LINE_SIZE, stdin))
                {
                    printf("Error: Error getting line from input file.\n");
                }
            }
            while(!(validate_new_record(user_input))); // should be validate just 1 thing..
            // delete record
            //long address = hash_func(temp_studentID, HASHTABLE_SIZE);

            break;
        }
        case '4':
        {
            // find and display certain record
            //long address = hash_func(temp_studentID, HASHTABLE_SIZE);
            //search_record(token, address, fp);
            break;
        }
        case '5':
            break;
        default:
        {
            printf("Error in switch statement in user menu.\n");
            exit(EXIT_FAILURE);
        }
        }
    }
    while(choice!='5');
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
        printf("   1. Display all current records in database.\n");
        printf("   2. Add new record entry into database.\n");
        printf("   3. Delete record from database.\n");
        printf("   4. Find and display certain record from database.\n");
        printf("   5. Quit.\n");
        printf("Enter an option (1, 2, 3, 4, or 5) : ");
        if(!fgets(line, LINE_SIZE, stdin))
        {
            printf("Error: Error getting user choice input.\n");
        }
        choice = (strlen(line)>2)? '0' : line[0];
    }
    while(choice<'1' || choice>'5');
    return choice;
}
