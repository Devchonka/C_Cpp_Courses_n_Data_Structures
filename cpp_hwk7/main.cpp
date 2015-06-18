/**
    CIS 29 : Advanced C++.
    Author: Elena Menyaylenko           Date: 06/08/2015
    Assignment: New and Delete memory management by address and number of bytes.
    To compile code:
         g++ -std=c++11 *.h *.cpp -o cpp_hwk5
    To check memory leaks with Valgrind:
        valgrind --tool=memcheck --leak-check=yes ./cpp_hwk6
    To use gdb:
    c++ -g *.cpp *.h -o cpp_hwk5
    gdb cpp_hw5
    break 42 or break main (set breakpoint line number or function)
    run
    c (continue) or s (step)
    print x


    Procedure:
    x 1) Read in entire file
    2) For every 10 lines : num+node
    3) Populate tuples, bar code
    4) Create unordered map

*/


#include <iostream>
#include "lexical_parser.h"

#define TUPLE_SIZE 7

using namespace std;

const string FNAME_IN = "Patient.xml";
const string FNAME_LOOKUP = "Barcodes.txt";

int main() //tuple : std::string, unsigned short, char, std::string, std::string, unsigned, unsigned short
{
    string* pText = read_entire_file(FNAME_IN);
    //cout<< *pText << endl;
    DataBase dBase(pText);
    delete(pText);
    return 0;
}
