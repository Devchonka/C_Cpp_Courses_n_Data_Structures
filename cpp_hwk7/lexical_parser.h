/**

*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <tuple>
#include <unordered_map>

typedef std::tuple<std::string, unsigned short, char, std::string, std::string, unsigned, unsigned short> PATIENT_REC;

std::string* read_entire_file(std::string);

class Patient
{
    PATIENT_REC _rec;

public:
    Patient(PATIENT_REC rec): _rec(rec) {};
    void print_rec();

};



class DataBase
{
    std::unordered_map<long, PATIENT_REC*> _barcode2Patient;
public:
    DataBase(std::string*);
};
