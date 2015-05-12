#ifndef RECORD_H
#define RECORD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct record RECORD;
struct record
{
    char  lastname[21];
    char  firstname[21];
    double amount;
    unsigned studentId; // exactly 4 digits: unsigned implies "unsigned int"
};

bool validate_new_record(char*);
bool has_only_allowed(char*, char*);
bool validate_name(char*);
bool validate_studentID(char*);
bool validate_amount(char*);



#endif // RECORD_H
