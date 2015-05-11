#ifndef RECORD_H
#define RECORD_H

typedef struct record RECORD;
struct record
{
    char  lastname[21];
    char  firstname[21];
    double amount;
    unsigned studentId; // exactly 4 digits: unsigned implies "unsigned int"
};








#endif // RECORD_H
