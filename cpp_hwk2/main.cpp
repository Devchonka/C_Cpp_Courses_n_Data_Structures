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
#include <cstring>
#include <bitset>
#include <algorithm>
#include <locale>
#include <cctype>

#include <typeinfo> // get type of variable
#include <sstream> // for parsing


#include "encryption_scheme_classes.h"
#include "Hashed_Dict.h"


using namespace std;

const string FNAME_MORSE = "morse_table_ascii.txt";

char* read_bin_file(string, int*);
unsigned int hashMap(const string&);


int main()
{
    string fname = "Morse.bin";
    int num_chars = 0;
    char* bitArray = read_bin_file(fname, &num_chars);
    Binary_Msg* bin_msg = new Binary_Msg(bitArray, &num_chars);
    //bin_msg->print_bit_msg();
    // cout << bin_msg->get_num_bits() << endl;zz
    // hashedDict<string, char>* hashTable = new hashedDict<string,char>(HASH_SIZE);
    // populateHash(hashTable);
    /*
        cout<<"Ave LL len: " << hashTable->getAveLLsize()<<endl;
        cout<<"num collisions: " << hashTable->getColl()<<endl;
        cout<<"num items in map: " << hashTable->getCount()<<endl;
        cout<<"load fac: " << hashTable->getLoadFac()<<endl;
    */
    Morse_Msg* mrs_msg = new Morse_Msg(bin_msg);
    //unsigned int (*hashFuncPtr)(const string&) = hashMap;
    // mrs_msg->print_morse_msg();
    // cout <<mrs_msg->get_num_words()<<endl;

    //string letter = "-..";
    //cout<< mrs_msg->morse_table.searchNode(letter, hashFuncPtr)<<endl;

    //Ascii_Msg* asc_msg = new Ascii_Msg(mrs_msg);

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

/**
    Hashing function using the rotating hashing algorithm. It folds internal state and combines it with each
    byte of input, to give better LL distribution.
*/
unsigned int hashMap(const string& key)
{
    size_t h = 0;
    for(std::size_t i = 0; i < key.size(); ++i)
    {
        h += (key.at(i) - '-' + 2) * (i + 1) * (i + 1);
    }
    //cout<<" string " <<key<<" is in index " << h % HASH_SIZE<<endl;
    return h % HASH_SIZE;
}


/**
    Builds hash from input file. Returns false and prints error if file not found.
*/
bool populateHash(hashedDict<string, char>& hashTable)
{
    ifstream fileHandle;
    fileHandle.open(FNAME_MORSE);
    bool ableToPopulate = fileHandle.good();
    if(ableToPopulate)
    {
        unsigned int (*hashFuncPtr)(const string&) = hashMap;
        string line =" ";
        char ascii_letter = ' ';
        string mrs_letter;


                while(getline(fileHandle, line))
                {
                    ascii_letter = line[0];
                    mrs_letter = line.substr(1);
                    hashTable.addNode(mrs_letter, ascii_letter, hashFuncPtr);
                }
                fileHandle.close();

    }
    else
    {
        cout << "Error: bad morse table file." <<endl;
        exit(EXIT_FAILURE);
    }
    return ableToPopulate;
}
