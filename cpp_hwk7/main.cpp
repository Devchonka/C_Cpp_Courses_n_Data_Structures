/**
    CIS 29 : Advanced C++.
    Author: Elena Menyaylenko           Date: 06/08/2015
    Assignment: New and Delete memory management by address and number of bytes.

    Note: This solution takes 26 sec. A more efficient solution will be implemented.

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

*/


#include <iostream>
#include <ctime>
#include "lexical_parser.h"

#define TUPLE_SIZE 7

using namespace std;

const string FNAME_IN = "Patient.xml";
const string FNAME_LOOKUP = "Barcodes.txt";

int main()
{
    Tester tester;
    tester.get_barcodes(FNAME_LOOKUP);
    string* pText = tester.read_entire_file(FNAME_IN);
    DataBase dBase;
    dBase.build_dataBase(pText);
    tester.lookupBarcodes(dBase);
    return 0;
}
