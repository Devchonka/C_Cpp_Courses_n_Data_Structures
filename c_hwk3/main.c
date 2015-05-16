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
    x 3) Create menu for user to allow 5 options (display all, quit)
        - insert
        - delete
        - find and display
    x 4) Create menu keyboard validation for user
     - names: only have letters
     - student id: exactly 4 digits
     - amount needs a decimal point number between 10-99999.99
    x 5) Make sure all string functions are strtok, strtod, etc
    x 6) Make sure arguments come from command line
    x 7) Create binary file
    8) Make all entries be in upper case

    8) Check memory leak detection using VALGRIND

    To compile code:
        gcc -std=c99  *.h *.c -o c_hwk3
    To check memory leaks with Valgrind:
        valgrind --tool=memcheck --leak-check=yes ./c_hwk3
************************************************************************/

#include "record.h"
const int LINE_SIZE = 512;
char* FNAME_BIN = "records.dat";

char* get_fname(char**);
void read_file(const char*, FILE*);
void user_menu(FILE*);
char get_user_choice();

int main(int argc, char* argv[])
{
    char* fname = get_fname(argv);
    FILE* fp_binary_out = create_hash_file(FNAME_BIN); // creates fileHandle to the output binary file
    read_file(fname, fp_binary_out);
    user_menu(fp_binary_out);
    fclose(fp_binary_out);
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
        printf("\n\tError: Please run the program with 1 argument (ie input_file.txt)\n");
        exit(1);
    }
    FILE* file = fopen(argv[1], "r");
    if(file == 0)
    {
        printf("\n\tError: Input file cannot be opened.\n");
        exit(1);
    }
    fclose(file);
    return argv[1];
}

/**
Function read_file. Reads a valid file and adds records into the hash.
*/
void read_file(const char* fname_in, FILE* fp_binary_out)
{
    printf("Reading in records from text file %s into binary file %s\n\n", fname_in, FNAME_BIN);
    char line[LINE_SIZE];
    FILE* ifp;
    ifp = fopen(fname_in, "r");
    int index = 0;
    if(fgets(line, LINE_SIZE, ifp)==NULL)
    {
        fprintf(stderr, "\n\tError: empty input file %s\n", fname_in);
        exit(EXIT_FAILURE);
    }
    char temp_Lname[21], temp_Fname[21];
    double temp_amount;
    unsigned int temp_sId;
    RECORD rec;
    while(fgets(line, LINE_SIZE, ifp))
    {
        if(line[0] != '\n')
        {
            line[strlen(line)-1] = '\0'; // get rid of newline
            rec = get_rec_from_valid_line(line);
            insert_record(rec, fp_binary_out);
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
            print_all_records(fp);
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
                    printf("\n\tError: Error getting line from user input.\n");
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
            char user_input_studentID[LINE_SIZE];
            do
            {
                putchar('\n');
                printf("****Delete record entry from database.****\n");
                printf("Enter student ID whose record you would like deleted: ");
                if(!fgets(user_input_studentID, LINE_SIZE, stdin))
                {
                    printf("\n\tError: Error getting line from input file.\n");
                }
                user_input_studentID[strlen(user_input_studentID)-1] = '\0'; // get rid of newline
            }
            while(!(validate_studentID(user_input_studentID))); // should be validate just 1 thing..
            RECORD delete_temp;
            delete_temp.studentId = atoi(user_input_studentID);
            long address =0;
            if(search_record(&delete_temp, &address, fp))  // if found...
            {
                delete_record(delete_temp.studentId, address, fp);
            }
            break;
        }
        case '4':
        {
            char user_input_studentID[LINE_SIZE];
            do
            {
                putchar('\n');
                printf("****Display a certain record in database.****\n");
                printf("Enter student ID whose record you would like displayed: ");
                if(!fgets(user_input_studentID, LINE_SIZE, stdin))
                {
                    printf("\n\tError: Error getting line from input file.\n");
                }
                user_input_studentID[strlen(user_input_studentID)-1] = '\0'; // get rid of newline
            }
            while(!(validate_studentID(user_input_studentID))); // should be validate just 1 thing..
            RECORD display_temp;
            display_temp.studentId = atoi(user_input_studentID);
            long address =0;
            if(search_record(&display_temp, &address, fp))  // if found...
            {
                print_rec_at_address(&display_temp);
            }
            break;
        }
        case '5':
            break;
        default:
        {
            printf("\n\tError: Error in options of the user menu.\n");
            exit(EXIT_FAILURE);
        }
        }
    }
    while(choice!='5');
}

/**
 Function get_user_choice. The function returns a valid choice provided from the user with validation.
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
            printf("\n\tError: Error getting user choice input.\n");
        }
        choice = (strlen(line)>2)? '0' : line[0];
    }
    while(choice<'1' || choice>'5');
    return choice;
}

/**
OUTPUT TESTING:
elena@elena-e5250 ~/CodeBlocksProjects/c_hwk3 $ ./c_hwk3 fin_aid.txt
Reading in records from text file fin_aid.txt into binary file records.dat

Record: 5675 :added to bucket 15.
Record: 1235 :added to bucket 15.
Record: 2341 :added to bucket 1.
Record: 8624 :added to bucket 4.
Record: 9162 :added to bucket 2.
Record: 7146 :added to bucket 6.
Record: 2328 :added to bucket 8.
Record: 1622 :added to bucket 2.
Record: 1832 :added to bucket 12.
Record: 3271 :added to bucket 11.
Record: 4717 :added to bucket 17.
Record: 9345 :added to bucket 5.
Record: 1623 :added to bucket 3.
Record: 5673 :added to bucket 13.
Record: 6275 :added to bucket 15.
Record: 5392 :added to bucket 12.
Record: 5555 :added to bucket 15.

********* MENU ************

   1. Display all current records in database.
   2. Add new record entry into database.
   3. Delete record from database.
   4. Find and display certain record from database.
   5. Quit.
Enter an option (1, 2, 3, 4, or 5) : 1

*****Display all current records in database.*****
2341 JONES BARBARA 74.23
9162 DAVIS SUSAN 902.34
1622 MOORE TONI 83.65
1623 CLARK VICTOR 83.45
8624 BROWN YELENA 56.75
9345 ROBINSON ANDRE 15.67
7146 MILLER ALISON 8934.12
2328 WILSON ROYCE 123.09
3271 GARCIA ROBERT 43.72
1832 TAYLOR JOAN 293.18
5392 HERNANDEZ MICHAEL 23.45
5673 HALL MARC 93.13
5675 JOHNSON SHEILA 23.91
1235 WILLIAMS JANE 93.12
6275 ALLEN RAY 958.34
5555 MENYAYLENKO YELENA 10.99
4717 MARTINEZ JHON 85.11

********* MENU ************

   1. Display all current records in database.
   2. Add new record entry into database.
   3. Delete record from database.
   4. Find and display certain record from database.
   5. Quit.
Enter an option (1, 2, 3, 4, or 5) : 2


****Add new record entry into database.****
Correct format: studentId FirstName LastName FinancialAid

Add new record in form similar to (6745 SMITH ANNA 7769.87): 1234 DELIA G 100.00
Record: 1234 :added to bucket 14.

********* MENU ************

   1. Display all current records in database.
   2. Add new record entry into database.
   3. Delete record from database.
   4. Find and display certain record from database.
   5. Quit.
Enter an option (1, 2, 3, 4, or 5) : 6

********* MENU ************

   1. Display all current records in database.
   2. Add new record entry into database.
   3. Delete record from database.
   4. Find and display certain record from database.
   5. Quit.
Enter an option (1, 2, 3, 4, or 5) : 2


****Add new record entry into database.****
Correct format: studentId FirstName LastName FinancialAid

Add new record in form similar to (6745 SMITH ANNA 7769.87): ERROR OH MY GOSH BLAH!
Please type in exactly 4 words: studentID FirstName LastName Amount

****Add new record entry into database.****
Correct format: studentId FirstName LastName FinancialAid

Add new record in form similar to (6745 SMITH ANNA 7769.87): ONE TWO THREE FOUR

	Error: Student IDs must be typed using 4 digits only.

	Error: Financial aid amount must be $10.00-99999.99 (2 digits after decimal point).


****Add new record entry into database.****
Correct format: studentId FirstName LastName FinancialAid

Add new record in form similar to (6745 SMITH ANNA 7769.87): 6666 ONE TWO 9

	Error: Financial aid amount must be $10.00-99999.99 (2 digits after decimal point).


****Add new record entry into database.****
Correct format: studentId FirstName LastName FinancialAid

Add new record in form similar to (6745 SMITH ANNA 7769.87): 1234 OKAY NOW 99.98
Record: 1234 :added to bucket 14.

********* MENU ************

   1. Display all current records in database.
   2. Add new record entry into database.
   3. Delete record from database.
   4. Find and display certain record from database.
   5. Quit.
Enter an option (1, 2, 3, 4, or 5) : 4

****Display a certain record in database.****
Enter student ID whose record you would like displayed: 1234
	1234 found
	at hash bucket 14.
1234 OKAY NOW 99.98

********* MENU ************

   1. Display all current records in database.
   2. Add new record entry into database.
   3. Delete record from database.
   4. Find and display certain record from database.
   5. Quit.
Enter an option (1, 2, 3, 4, or 5) : 3

****Delete record entry from database.****
Enter student ID whose record you would like deleted: 5555
	5555 found
	at hash bucket 15.
Record: 5555 :deleted from bucket 15.

********* MENU ************

   1. Display all current records in database.
   2. Add new record entry into database.
   3. Delete record from database.
   4. Find and display certain record from database.
   5. Quit.
Enter an option (1, 2, 3, 4, or 5) : 1

*****Display all current records in database.*****
2341 JONES BARBARA 74.23
9162 DAVIS SUSAN 902.34
1622 MOORE TONI 83.65
1623 CLARK VICTOR 83.45
8624 BROWN YELENA 56.75
9345 ROBINSON ANDRE 15.67
7146 MILLER ALISON 8934.12
2328 WILSON ROYCE 123.09
3271 GARCIA ROBERT 43.72
1832 TAYLOR JOAN 293.18
5392 HERNANDEZ MICHAEL 23.45
5673 HALL MARC 93.13
1234 OKAY NOW 99.98
5675 JOHNSON SHEILA 23.91
1235 WILLIAMS JANE 93.12
6275 ALLEN RAY 958.34
4717 MARTINEZ JHON 85.11

********* MENU ************

   1. Display all current records in database.
   2. Add new record entry into database.
   3. Delete record from database.
   4. Find and display certain record from database.
   5. Quit.
Enter an option (1, 2, 3, 4, or 5) : 4

****Display a certain record in database.****
Enter student ID whose record you would like displayed: 5555
Records with key: 5555 : not found.

********* MENU ************

   1. Display all current records in database.
   2. Add new record entry into database.
   3. Delete record from database.
   4. Find and display certain record from database.
   5. Quit.
Enter an option (1, 2, 3, 4, or 5) : 5
elena@elena-e5250 ~/CodeBlocksProjects/c_hwk3 $


VALIGRIND OUTPUT:
elena@elena-e5250 ~/CodeBlocksProjects/c_hwk3 $ valgrind --tool=memcheck --leak-check=yes ./c_hwk3
==7319== Memcheck, a memory error detector
==7319== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==7319== Using Valgrind-3.10.0.SVN and LibVEX; rerun with -h for copyright info
==7319== Command: ./c_hwk3
==7319==

	Error: Please run the program with 1 argument (ie input_file.txt)
==7319==
==7319== HEAP SUMMARY:
==7319==     in use at exit: 0 bytes in 0 blocks
==7319==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==7319==
==7319== All heap blocks were freed -- no leaks are possible
==7319==
==7319== For counts of detected and suppressed errors, rerun with: -v
==7319== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
elena@elena-e5250 ~/CodeBlocksProjects/c_hwk3 $ valgrind --tool=memcheck --leak-check=yes ./c_hwk3 fin_aid.txt
==7320== Memcheck, a memory error detector
==7320== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==7320== Using Valgrind-3.10.0.SVN and LibVEX; rerun with -h for copyright info
==7320== Command: ./c_hwk3 fin_aid.txt
==7320==
Reading in records from text file fin_aid.txt into binary file records.dat

==7320== Conditional jump or move depends on uninitialised value(s)
==7320==    at 0x401BCF: make_toUpper (in /home/elena/CodeBlocksProjects/c_hwk3/c_hwk3)
==7320==    by 0x401C11: insert_record (in /home/elena/CodeBlocksProjects/c_hwk3/c_hwk3)
==7320==    by 0x400EA0: read_file (in /home/elena/CodeBlocksProjects/c_hwk3/c_hwk3)
==7320==    by 0x400C5A: main (in /home/elena/CodeBlocksProjects/c_hwk3/c_hwk3)
==7320==
==7320== Conditional jump or move depends on uninitialised value(s)
==7320==    at 0x4E66E4F: toupper (ctype.c:52)
==7320==    by 0x401BA5: make_toUpper (in /home/elena/CodeBlocksProjects/c_hwk3/c_hwk3)
==7320==    by 0x401C11: insert_record (in /home/elena/CodeBlocksProjects/c_hwk3/c_hwk3)
==7320==    by 0x400EA0: read_file (in /home/elena/CodeBlocksProjects/c_hwk3/c_hwk3)
==7320==    by 0x400C5A: main (in /home/elena/CodeBlocksProjects/c_hwk3/c_hwk3)
==7320==
==7320== Use of uninitialised value of size 8
==7320==    at 0x4E66E63: toupper (ctype.c:52)
==7320==    by 0x401BA5: make_toUpper (in /home/elena/CodeBlocksProjects/c_hwk3/c_hwk3)
==7320==    by 0x401C11: insert_record (in /home/elena/CodeBlocksProjects/c_hwk3/c_hwk3)
==7320==    by 0x400EA0: read_file (in /home/elena/CodeBlocksProjects/c_hwk3/c_hwk3)
==7320==    by 0x400C5A: main (in /home/elena/CodeBlocksProjects/c_hwk3/c_hwk3)
==7320==
==7320== Conditional jump or move depends on uninitialised value(s)
==7320==    at 0x401BCF: make_toUpper (in /home/elena/CodeBlocksProjects/c_hwk3/c_hwk3)
==7320==    by 0x401C1A: insert_record (in /home/elena/CodeBlocksProjects/c_hwk3/c_hwk3)
==7320==    by 0x400EA0: read_file (in /home/elena/CodeBlocksProjects/c_hwk3/c_hwk3)
==7320==    by 0x400C5A: main (in /home/elena/CodeBlocksProjects/c_hwk3/c_hwk3)
==7320==
Record: 5675 :added to bucket 15.
==7320== Syscall param write(buf) points to uninitialised byte(s)
==7320==    at 0x4F22870: __write_nocancel (syscall-template.S:81)
==7320==    by 0x4EB0002: _IO_file_write@@GLIBC_2.2.5 (fileops.c:1261)
==7320==    by 0x4EB14DB: _IO_do_write@@GLIBC_2.2.5 (fileops.c:538)
==7320==    by 0x4EB21CE: _IO_switch_to_get_mode (genops.c:184)
==7320==    by 0x4EAF9BD: _IO_file_seekoff@@GLIBC_2.2.5 (fileops.c:969)
==7320==    by 0x4EA8A26: fseek (fseek.c:39)
==7320==    by 0x401C39: insert_record (in /home/elena/CodeBlocksProjects/c_hwk3/c_hwk3)
==7320==    by 0x400EA0: read_file (in /home/elena/CodeBlocksProjects/c_hwk3/c_hwk3)
==7320==    by 0x400C5A: main (in /home/elena/CodeBlocksProjects/c_hwk3/c_hwk3)
==7320==  Address 0x4025007 is not stack'd, malloc'd or (recently) free'd
==7320==
Record: 1235 :added to bucket 15.
Record: 2341 :added to bucket 1.
Record: 8624 :added to bucket 4.
Record: 9162 :added to bucket 2.
Record: 7146 :added to bucket 6.
Record: 2328 :added to bucket 8.
Record: 1622 :added to bucket 2.
Record: 1832 :added to bucket 12.
Record: 3271 :added to bucket 11.
Record: 4717 :added to bucket 17.
Record: 9345 :added to bucket 5.
Record: 1623 :added to bucket 3.
Record: 5673 :added to bucket 13.
Record: 6275 :added to bucket 15.
Record: 5392 :added to bucket 12.
Record: 5555 :added to bucket 15.

********* MENU ************

   1. Display all current records in database.
   2. Add new record entry into database.
   3. Delete record from database.
   4. Find and display certain record from database.
   5. Quit.
Enter an option (1, 2, 3, 4, or 5) : 5
==7320== Syscall param write(buf) points to uninitialised byte(s)
==7320==    at 0x4F22870: __write_nocancel (syscall-template.S:81)
==7320==    by 0x4EB0002: _IO_file_write@@GLIBC_2.2.5 (fileops.c:1261)
==7320==    by 0x4EB14DB: _IO_do_write@@GLIBC_2.2.5 (fileops.c:538)
==7320==    by 0x4EB0D5F: _IO_file_close_it@@GLIBC_2.2.5 (fileops.c:165)
==7320==    by 0x4EA4B0F: fclose@@GLIBC_2.2.5 (iofclose.c:59)
==7320==    by 0x400C72: main (in /home/elena/CodeBlocksProjects/c_hwk3/c_hwk3)
==7320==  Address 0x4025fc7 is not stack'd, malloc'd or (recently) free'd
==7320==
==7320==
==7320== HEAP SUMMARY:
==7320==     in use at exit: 0 bytes in 0 blocks
==7320==   total heap usage: 3 allocs, 3 frees, 1,704 bytes allocated
==7320==
==7320== All heap blocks were freed -- no leaks are possible
==7320==
==7320== For counts of detected and suppressed errors, rerun with: -v
==7320== Use --track-origins=yes to see where uninitialised values come from
==7320== ERROR SUMMARY: 54 errors from 6 contexts (suppressed: 0 from 0)

*/
