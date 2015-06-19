/**

*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <tuple>
#include <vector>
#include <unordered_map>
#include <regex>

typedef std::tuple<std::string, unsigned short, char, std::string, std::string, unsigned, unsigned short> PATIENT_REC;

std::string* read_entire_file(std::string);

class RegEx_Utility
{
private:
    std::string* _contents;
public:
    RegEx_Utility(std::string* contents): _contents(contents) {};
    ~RegEx_Utility() {};
    std::vector<std::string> extract_substring(std::string, bool);
};

class Patient
{
    PATIENT_REC _rec;

public:
    Patient(PATIENT_REC rec): _rec(rec) {};
    void print_rec();

};


class DataBase
{
    std::unordered_map<long, Patient*> _barcode2Patient;

public:
    DataBase(): _barcode2Patient({}) {};
    ~DataBase();
    void build_dataBase(std::string*);
    //void search_patients();
};
