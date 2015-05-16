/**
Record.h
File that contains all files related to the RECORD struct and its validation.
*/

#ifndef RECORD_H
#define RECORD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define TABSIZE 20
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

long hash_func(int, int);  // hash by student ID
FILE* create_hash_file(char*);

bool insert_record(RECORD, FILE*);
bool delete_record(unsigned, long, FILE*);
bool search_record(RECORD*, long*, FILE*);
void print_rec_at_address(RECORD*);
void print_all_records(FILE*);

#endif // RECORD_H
