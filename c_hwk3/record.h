#ifndef RECORD_H
#define RECORD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


#define TABSIZE 31
#define OFLOWSIZE 100
#define BUCKETSIZE 4 // structs per bucket

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
RECORD get_rec_from_valid_line(char*);

long hash_func (int, int); // hash by student ID
FILE* create_hash_file(char*);

void insert_record(RECORD, FILE*);
void search_record(char*, long, FILE*);

#endif // RECORD_H
