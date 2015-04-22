/*********************************************************************************
** CIS 26B													    Spring, 2015
** Advanced C++ Hwk 2
**  Written By: Menyaylenko, Elena
**
**  IDE (compiler):     GNU GCC Compiler, Unix OS
**
**  Assignment: Decode encrypted message in binary using Morse code.
**
    Procedure:
    x 1) Read Morse.bin
    x 2) Create Binary_Msg object
    x 3) Create Morse_Msg object
    4) Create hashed table containing values lookup
    5) Create Ascii_Msg object
    6) Display encrypted message to screen


    To compile code:
         // gcc -std=c99  main.c defines.h defines.c -o c_hwk1
    To check memory leaks with Valgrind:
        // valgrind --tool=memcheck --leak-check=yes ./c_hwk1
************************************************************************/

#include <fstream>
#include <iostream>
#include <string>
#include <bitset>


#include "encryption_scheme_classes.h"

using namespace std;

char* read_bin_file(string, int*);


int main()
{
    string fname = "Morse.bin";
    int num_chars = 0;
    char* bitArray = read_bin_file(fname, &num_chars);
    Binary_Msg* bin_msg = new Binary_Msg(bitArray, &num_chars);
    //bin_msg->print_bit_msg();
    // cout << bin_msg->get_num_bits() << endl;

    Morse_Msg* mrs_msg = new Morse_Msg(bin_msg);
    // mrs_msg->print_morse_msg();
    // cout <<mrs_msg->get_num_words()<<endl;


    delete bin_msg;
    delete mrs_msg;
    delete[] bitArray;
    return 0;
}

char* read_bin_file(string fname, int* num_chars)
{
    // Based on: http://www.cplusplus.com/doc/tutorial/files/
    streampos file_size;
    char* memblock = nullptr;
    ifstream fileHandle(fname, ios::in|ios::binary|ios::ate);
    if(fileHandle.is_open())
    {
        file_size = fileHandle.tellg();
        memblock = new char [file_size];
        fileHandle.seekg(0, ios::beg);
        fileHandle.read(memblock, file_size);
        fileHandle.close();
        *num_chars = file_size;
    }
    else
    {
        cout << "Error: Unable to open input file " << fname <<"."<<endl;
        exit(EXIT_FAILURE);
    }
    return memblock;
}
