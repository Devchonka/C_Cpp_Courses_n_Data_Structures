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
    1) Create a user menu following requirements given
    2) Write on/off masks for flipping bits for options 1-8 of the menu
    3)

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
#include <stdbool.h>

// USE MACROS AND INLINE ALSO SEPARATE BITS BY 4 BITS EACH! SHE GIVES EXAMPLES
// macros to do bit shifting

void user_menu(unsigned short*);
char get_user_choice();
void turn_bits_onoff(unsigned short*, int, int, bool); // pg 173, 174, 175

void printbits(unsigned short);

const int LINE_SIZE = 256;

int main()
{
    unsigned short lights = 0;
    unsigned short* pLights = &lights;
    user_menu(pLights);
    return 0;
}

void user_menu(unsigned short* pLights)
{
    char choice;
    do
    {
        printbits(*pLights);
        choice = get_user_choice();
        switch(choice)
        {
        case '1':
        {
            putchar('\n');
            printf("*****Option 1: Turn on all lights.*****\n");
            turn_bits_onoff(pLights, 16, 0, 1);
            break;
        }
        case '2':
        {
            putchar('\n');
            printf("*****Option 2: Turn on center stage lights (lights 5-10).*****\n");
            turn_bits_onoff(pLights, 6, 5, 1);
            break;
        }
        case '3':
        {
            putchar('\n');
            printf("*****Option 3: Turn on left stage lights (lights 11-15).*****\n");
            turn_bits_onoff(pLights, 5, 11, 1);
            break;
        }
        case '4':
        {
            putchar('\n');
            printf("*****Option 4: Turn on right stage lights (lights 0-4).*****\n");
            turn_bits_onoff(pLights, 5, 0, 1);
            break;
        }
        case '5':
        {
            putchar('\n');
            printf("*****Option 5: Turn off all lights.*****\n");
            turn_bits_onoff(pLights, 16, 0, 0);
            break;
        }
        case '6':
        {
            putchar('\n');
            printf("*****Option 6: Turn off center stage lights.*****\n");
            turn_bits_onoff(pLights, 6, 5, 0);
            break;
        }
        case '7':
        {
            putchar('\n');
            printf("*****Option 7: Turn off left stage lights.*****\n");
            turn_bits_onoff(pLights, 5, 11, 0);
            break;
        }
        case '8':
        {
            putchar('\n');
            printf("*****Option 8: Turn off right stage lights.*****\n");
            turn_bits_onoff(pLights, 5, 0, 0);
            break;
        }
        case '9':
        {
            putchar('\n');
            printf("*****Option 9: Overlay on/off pattern onto light configuration.*****\n");
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
        printf("\nEnter an option (1, 2, 3, ... 10) : ");
        if(!fgets(line, LINE_SIZE, stdin))
        {
            printf("\n\tError: Error getting user choice input.\n");
        }
        if(line[0] != '\n')
        {
            line[strlen(line)-1] = '\0'; // get rid of newline
        }
        if((strcmp(line, "0")==0) || ((strcmp(line, "10")!=0) && strlen(line)>1))
        {
            strcpy(line, "x");
        }
        if(strcmp(line, "10")==0 || line[0]=='\n')
        {
            strcpy(line,"0");
        }
        choice = line[0];
    }
    while(choice<'0' || choice>'9');
    return choice;
}

void turn_bits_onoff(unsigned short* pLights, int numBits, int startBit, bool onoff)
{
    if(onoff)
    {
        printf("Turn ON %d bits starting at bit #%d\n", numBits, startBit);
        unsigned short mask = (~(((unsigned short)~0) << numBits)) << startBit;
        *pLights = *pLights | mask;
    }
    else
    {
        printf("Turn OFF %d bits starting at bit #%d\n", numBits, startBit);
        unsigned short mask = ~((~(((unsigned short) ~0) << numBits)) << startBit);
        *pLights = *pLights & mask;
    }
}

/**
   This uses a trick to print an unsigned short as a string of 16 bits
*/
void printbits(unsigned short lights)
{
    printf("\nCurrent Light Configuration: ");
    int  testbit(unsigned short lights, int bit_to_test);
    int i;
    for(i = 15; i >= 0; i--)
    {
        if (!((i+1) % 4))
            printf(" ");
        printf("%1d", testbit(lights, i));
    }
    printf("\n");
}

/**
   Return 1 if bit_to_test is set and 0 if it is unset
*/
int  testbit(unsigned short lights, int bit_to_test)
{
    lights >>= bit_to_test;
    lights &= 1;
    return lights;
}
