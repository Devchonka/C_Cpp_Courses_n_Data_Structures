#include "record.h"


/**
Function validate_new_record. Takes in a line, breaks it down to tokens, and if there are exactly 4 entries, it
sends off each bit to be validated individually. It returns a true/false value of whether each token passed.
*/

bool validate_new_record(char* record_line)
{
    bool valid = false;
    char* tokenArray[21];
    int counter =0;
    for(char* p = strtok(record_line," "); p != NULL; p = strtok(NULL, " "))
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

