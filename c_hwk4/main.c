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
    2) Write on/off masks for flipping selected bits on and off for options 1-8
    3) Add in macros, strtok and strtol
    4) Write overlay function for option 9

    To compile code:
        gcc -std=c99  *.h *.c -o c_hwk4
    To check memory leaks with Valgrind: - no dynamic allocations in this code
        valgrind --tool=memcheck --leak-check=yes ./c_hwk4
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Defining MACROs to deal with common operations
#define GET_USER_LINE(line) if(!fgets(line, sizeof(line), stdin)) {\
            printf("\n\tError: Error getting user choice input.\n"); exit(1);}

#define DELETE_NEWLINE(line) if(line[0] != '\n'){line[strlen(line)-1] = '\0';}

#define PATTERN_IN_BOUNDS(numBits, startBit) ((16-startBit)>= numBits)

/**
    A constant table of user options for the menu. Declared globally for potential to reuse it,
    thus const char* const for safety.
*/
const char* const OptionsTable[]  =
{
    "   1. Turn on all lights.",
    "   2. Turn on stage lights (lights 5-10).",
    "   3. Turn on left stage lights (lights 11-15).",
    "   4. Turn on right stage lights (lights 0-4).",
    "   5. Turn off all lights.",
    "   6. Turn off center stage lights.",
    "   7. Turn off left stage lights.",
    "   8. Turn off right stage lights.",
    "   9. Overlay on/off pattern onto light configuration.",
    "   10. Quit."
} ;
void user_menu(unsigned short*);
char get_user_choice();
void turn_bits_onoff(unsigned short*, int, int, bool);
void overlay(unsigned short*, int, int, unsigned short);
unsigned short get_user_overlay(int*, int*);
bool validate_overlay_input(char*, int*, int*);
void printbits(unsigned short);
inline bool has_only_allowed(char*, char*);

/**
    Function main creates the lights and passes it to the repeating user menu.
*/
int main()
{
    unsigned short lights = 0;
    unsigned short* pLights = &lights;
    user_menu(pLights);
    return 0;
}

/**
    Function user_menu to execute the choice that user selected. For option 9, in the case
    that startBit is set to -1, the menu just recycles.
*/
void user_menu(unsigned short* pLights)
{
    char choice;
    do
    {
        printf("\nCurrent Light Configuration: ");
        printbits(*pLights);
        choice = get_user_choice();
        switch(choice)
        {
        case '1':
        {
            turn_bits_onoff(pLights, 16, 0, 1);
            break;
        }
        case '2':
        {
            turn_bits_onoff(pLights, 6, 5, 1);
            break;
        }
        case '3':
        {
            turn_bits_onoff(pLights, 5, 11, 1);
            break;
        }
        case '4':
        {
            turn_bits_onoff(pLights, 5, 0, 1);
            break;
        }
        case '5':
        {
            turn_bits_onoff(pLights, 16, 0, 0);
            break;
        }
        case '6':
        {
            turn_bits_onoff(pLights, 6, 5, 0);
            break;
        }
        case '7':
        {
            turn_bits_onoff(pLights, 5, 11, 0);
            break;
        }
        case '8':
        {
            turn_bits_onoff(pLights, 5, 0, 0);
            break;
        }
        case '9':
        {
            int startBit =0, numBits =0;
            int *pStartBit = &startBit, *pNumBits = &numBits;
            unsigned short pattern = get_user_overlay(pStartBit, pNumBits);
            if (startBit != -1)
                overlay(pLights, *pStartBit, *pNumBits, pattern);
            break;
        }
        case '0':
            break;
        default:
        {
            printf("\n\tError: Error in options of the user menu.\n");
            exit(1);
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
    char choice, line[256];
    do
    {
        printf("\n********* MENU ************\n\n");
        int i =0;
        for (; i<10;i++)
            printf("%s\n", OptionsTable[i]);
        printf("\n\tEnter an option (1, 2, 3, ... 10) : ");
        GET_USER_LINE(line);
        DELETE_NEWLINE(line);
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

/**
    Function turn_bits_onoff returns updated lights, and takes in the number of bits selected by user,
    and the starting bit for the modification.
*/
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
   Function printbits uses a trick to print an unsigned short as a string of 16 bits
*/
void printbits(unsigned short lights)
{
    int  testbit(unsigned short lights, int bit_to_test);
    int i;
    for(i = 15; i >= 0; i--)
    {
        if(!((i+1) % 4))
        {
            printf(" ");
        }
        printf("%1d", testbit(lights, i));
    }
    printf("\n");
}

/**
   Function testbit return 1 if bit_to_test is set and 0 if it is unset.
*/
int  testbit(unsigned short lights, int bit_to_test)
{
    lights >>= bit_to_test;
    lights &= 1;
    return lights;
}

/**
   Function overlay overlays a bit pattern on a range of bits coming from the user.
*/
void overlay(unsigned short* pLights, int startBit, int numBits, unsigned short pattern)
{
    printf("\nStart at bit #%d and overlay the right-most %d bits from pattern:\n\t", startBit, numBits);
    printbits(pattern);
    *pLights &= ~(~((unsigned short) ~0 << numBits) << startBit);
    *pLights |= pattern << startBit;
}

/**
   Function get_user_overlay obtains user preferences, returning a copy of the valid pattern.
   The function updates values of the starting bit and the number of bits selected by the user.
   Function sets starting bit to -1 if user entered newline to exit out of the menu option.
*/
unsigned short get_user_overlay(int* startBit, int* numBits)
{
    char line[256], *endpointer;
    do
    {
        printf("Enter bit pattern and starting bit for the overlay (ie 1001 3): ");
        GET_USER_LINE(line);
        DELETE_NEWLINE(line);
    }
    while(!validate_overlay_input(line, startBit, numBits));
    return (unsigned short) strtol(line, &endpointer, 2);
}

/**
    Function validate_overlay_input attempts to validate user input and update selected values
    such as the start bit and number of bits, and line contains only the pattern.
*/
bool validate_overlay_input(char line[], int* startBit, int* numBits)
{
    if(line[0]=='\n')
    {
        *startBit = -1;
       return true;
    }
    bool valid;
    char temp_string[64];
    strcpy(temp_string, line);
    strtok(temp_string,"\040\t"); // temp_string is the bit pattern now
    valid = has_only_allowed(temp_string, "01");

    if(valid)
    {
        strcpy(temp_string, strtok(NULL,"\040\t")); // temp_string now holds the startBit
        valid = has_only_allowed(temp_string, "0123456789");
    }
    if(valid)
    {
        strtok(line,"\040\t"); // tokenize pattern from line in caller function
        *startBit = atoi(temp_string);
        *numBits = strlen(line);
        if (*numBits > 16 || !PATTERN_IN_BOUNDS(*numBits, *startBit))
            valid = false;
    }
    if (!valid)
        printf("Please type in bit pattern and starting bit in format such as 1101 5.\n");
    return valid;
}

/**
 Function has_only_allowed is used to ensure only allowed characters are validated.
*/
inline bool has_only_allowed(char* string, char* allowed)
{
    return !(strspn(string, allowed)<strlen(string));
}

/************ SAMPLE OUTPUT:

Current Light Configuration:  0000 0000 0000 0000

********* MENU ************

   1. Turn on all lights.
   2. Turn on stage lights (lights 5-10).
   3. Turn on left stage lights (lights 11-15).
   4. Turn on right stage lights (lights 0-4).
   5. Turn off all lights.
   6. Turn off center stage lights.
   7. Turn off left stage lights.
   8. Turn off right stage lights.
   9. Overlay on/off pattern onto light configuration.
   10. Quit.

	Enter an option (1, 2, 3, ... 10) : 3
Turn ON 5 bits starting at bit #11

Current Light Configuration:  1111 1000 0000 0000

********* MENU ************

   1. Turn on all lights.
   2. Turn on stage lights (lights 5-10).
   3. Turn on left stage lights (lights 11-15).
   4. Turn on right stage lights (lights 0-4).
   5. Turn off all lights.
   6. Turn off center stage lights.
   7. Turn off left stage lights.
   8. Turn off right stage lights.
   9. Overlay on/off pattern onto light configuration.
   10. Quit.

	Enter an option (1, 2, 3, ... 10) : 5
Turn OFF 16 bits starting at bit #0

Current Light Configuration:  0000 0000 0000 0000

********* MENU ************

   1. Turn on all lights.
   2. Turn on stage lights (lights 5-10).
   3. Turn on left stage lights (lights 11-15).
   4. Turn on right stage lights (lights 0-4).
   5. Turn off all lights.
   6. Turn off center stage lights.
   7. Turn off left stage lights.
   8. Turn off right stage lights.
   9. Overlay on/off pattern onto light configuration.
   10. Quit.

	Enter an option (1, 2, 3, ... 10) : 2
Turn ON 6 bits starting at bit #5

Current Light Configuration:  0000 0111 1110 0000

********* MENU ************

   1. Turn on all lights.
   2. Turn on stage lights (lights 5-10).
   3. Turn on left stage lights (lights 11-15).
   4. Turn on right stage lights (lights 0-4).
   5. Turn off all lights.
   6. Turn off center stage lights.
   7. Turn off left stage lights.
   8. Turn off right stage lights.
   9. Overlay on/off pattern onto light configuration.
   10. Quit.

	Enter an option (1, 2, 3, ... 10) : 3
Turn ON 5 bits starting at bit #11

Current Light Configuration:  1111 1111 1110 0000

********* MENU ************

   1. Turn on all lights.
   2. Turn on stage lights (lights 5-10).
   3. Turn on left stage lights (lights 11-15).
   4. Turn on right stage lights (lights 0-4).
   5. Turn off all lights.
   6. Turn off center stage lights.
   7. Turn off left stage lights.
   8. Turn off right stage lights.
   9. Overlay on/off pattern onto light configuration.
   10. Quit.

	Enter an option (1, 2, 3, ... 10) : 4
Turn ON 5 bits starting at bit #0

Current Light Configuration:  1111 1111 1111 1111

********* MENU ************

   1. Turn on all lights.
   2. Turn on stage lights (lights 5-10).
   3. Turn on left stage lights (lights 11-15).
   4. Turn on right stage lights (lights 0-4).
   5. Turn off all lights.
   6. Turn off center stage lights.
   7. Turn off left stage lights.
   8. Turn off right stage lights.
   9. Overlay on/off pattern onto light configuration.
   10. Quit.

	Enter an option (1, 2, 3, ... 10) : 6
Turn OFF 6 bits starting at bit #5

Current Light Configuration:  1111 1000 0001 1111

********* MENU ************

   1. Turn on all lights.
   2. Turn on stage lights (lights 5-10).
   3. Turn on left stage lights (lights 11-15).
   4. Turn on right stage lights (lights 0-4).
   5. Turn off all lights.
   6. Turn off center stage lights.
   7. Turn off left stage lights.
   8. Turn off right stage lights.
   9. Overlay on/off pattern onto light configuration.
   10. Quit.

	Enter an option (1, 2, 3, ... 10) : 8
Turn OFF 5 bits starting at bit #0

Current Light Configuration:  1111 1000 0000 0000

********* MENU ************

   1. Turn on all lights.
   2. Turn on stage lights (lights 5-10).
   3. Turn on left stage lights (lights 11-15).
   4. Turn on right stage lights (lights 0-4).
   5. Turn off all lights.
   6. Turn off center stage lights.
   7. Turn off left stage lights.
   8. Turn off right stage lights.
   9. Overlay on/off pattern onto light configuration.
   10. Quit.

	Enter an option (1, 2, 3, ... 10) : 7
Turn OFF 5 bits starting at bit #11

Current Light Configuration:  0000 0000 0000 0000

********* MENU ************

   1. Turn on all lights.
   2. Turn on stage lights (lights 5-10).
   3. Turn on left stage lights (lights 11-15).
   4. Turn on right stage lights (lights 0-4).
   5. Turn off all lights.
   6. Turn off center stage lights.
   7. Turn off left stage lights.
   8. Turn off right stage lights.
   9. Overlay on/off pattern onto light configuration.
   10. Quit.

	Enter an option (1, 2, 3, ... 10) : 4
Turn ON 5 bits starting at bit #0

Current Light Configuration:  0000 0000 0001 1111

********* MENU ************

   1. Turn on all lights.
   2. Turn on stage lights (lights 5-10).
   3. Turn on left stage lights (lights 11-15).
   4. Turn on right stage lights (lights 0-4).
   5. Turn off all lights.
   6. Turn off center stage lights.
   7. Turn off left stage lights.
   8. Turn off right stage lights.
   9. Overlay on/off pattern onto light configuration.
   10. Quit.

	Enter an option (1, 2, 3, ... 10) : 9
Enter bit pattern and starting bit for the overlay (ie 1001 3): BLAH BLAH
Please type in bit pattern and starting bit in format such as 1101 5.
Enter bit pattern and starting bit for the overlay (ie 1001 3): 1234 5
Please type in bit pattern and starting bit in format such as 1101 5.
Enter bit pattern and starting bit for the overlay (ie 1001 3): 11000 7

Start at bit #7 and overlay the right-most 5 bits from pattern:
	 0000 0000 0001 1000

Current Light Configuration:  0000 1100 0001 1111

********* MENU ************

   1. Turn on all lights.
   2. Turn on stage lights (lights 5-10).
   3. Turn on left stage lights (lights 11-15).
   4. Turn on right stage lights (lights 0-4).
   5. Turn off all lights.
   6. Turn off center stage lights.
   7. Turn off left stage lights.
   8. Turn off right stage lights.
   9. Overlay on/off pattern onto light configuration.
   10. Quit.

	Enter an option (1, 2, 3, ... 10) : 9
Enter bit pattern and starting bit for the overlay (ie 1001 3): 0 0

Start at bit #0 and overlay the right-most 1 bits from pattern:
	 0000 0000 0000 0000

Current Light Configuration:  0000 1100 0001 1110
...
*/
