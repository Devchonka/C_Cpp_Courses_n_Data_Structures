/*********************************************************************************
** CIS 26B                                                            Spring, 2015
** Advanced C
******************
**
** Homework 3: Bit Manipulation. Simulation of a theater with 16 lights to flip.
**********************************************************************************
**  Written By: Menyaylenko, Elena
**
**  Date:               05/28/2015
**  IDE (compiler):     GNU GCC Compiler, Unix OS
**
    Procedure:
    1)

    ...
    x) Check memory leak detection using VALGRIND

    To compile code:
        gcc -std=c99  *.h *.c -o c_hwk4
    To check memory leaks with Valgrind:
        valgrind --tool=memcheck --leak-check=yes ./c_hwk4
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void user_menu();
char get_user_choice();

const int LINE_SIZE = 256;

int main()
{
    user_menu();
    return 0;
}

void user_menu()
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
            printf("*****Option 1...*****\n");
            // do stuff..
            break;
        }
        case '2':
        {
            putchar('\n');
            printf("*****Option 2...*****\n");
            // do stuff..
            break;
        }
        case '3':
                {
            putchar('\n');
            printf("*****Option 3...*****\n");
            // do stuff..
            break;
        }
        case '4':
                {
            putchar('\n');
            printf("*****Option 4...*****\n");
            // do stuff..
            break;
        }
        case '5':
                    {
            putchar('\n');
            printf("*****Option 5...*****\n");
            // do stuff..
            break;
        }
        case '6':
                    {
            putchar('\n');
            printf("*****Option 6...*****\n");
            // do stuff..
            break;
        }
        case '7':
                    {
            putchar('\n');
            printf("*****Option 7...*****\n");
            // do stuff..
            break;
        }
        case '8':
                    {
            putchar('\n');
            printf("*****Option 8...*****\n");
            // do stuff..
            break;
        }
        case '9':
                    {
            putchar('\n');
            printf("*****Option 9...*****\n");
            // do stuff..
            break;
        }
        case '0':
            break;
        default:
        {
            printf("\n\tError: Error in options of the user menu.\n");
            exit(EXIT_FAILURE);
        }
        }
    }
    while(choice!='0');
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
        printf("   1. Turn on all lights.\n");
        printf("   2. Turn on stage lights (lights 5-10).\n");
        printf("   3. Turn on left stage lights (lights 11-15).\n");
        printf("   4. Turn on right stage lights (lights 0-4).\n");
        printf("   5. Turn off all lights.\n");
        printf("   6. Turn off center stage lights.\n");
        printf("   7. Turn off left stage lights.\n");
        printf("   8. Turn off right stage lights.\n");
        printf("   9. Overlay on/off pattern onto light configuration.\n");
        printf("   10. Quit.\n");
        printf("Enter an option (1, 2, 3, ... 10) : ");
        if(!fgets(line, LINE_SIZE, stdin))
        {
            printf("\n\tError: Error getting user choice input.\n");
        }
        if (strcmp(line, "10"))
            strcpy(line,"0");
        choice = (strlen(line)>2)? '-1' : line[0];
    }
    while(choice<'0' || choice>'9');
    return choice;
}
