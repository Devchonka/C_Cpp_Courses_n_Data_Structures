#ifndef ENCRYPTION_SCHEME_CLASSES_H
#define ENCRYPTION_SCHEME_CLASSES_H

#include <iostream>
#include <bitset>
#include <string>
#include <vector>

#include "Hashed_Dict.h"
unsigned int hashMap(const std::string&);

class Binary_Msg
{
    std::vector< std::bitset<2> > _bin_msg;
    int _num_bits;

public:
    Binary_Msg(char*, int*); // constructor
    ~Binary_Msg() {}; // destructor

    std::bitset<2> get_bits(int);
    int get_num_bits();
    void print_bit_msg();
};


class Morse_Msg
{
    Binary_Msg* _bin_msg;
    std::vector<std::string> _mrs_msg;


public:
    hashedDict<std::string, char> morse_table;

    Morse_Msg(Binary_Msg*); // constructor
    //Morse_Msg(const Morse_Msg&){}; // copy constructor
    ~Morse_Msg() {}; // destructor

    Morse_Msg& operator = (const Morse_Msg&);

    int get_num_words();
    std::string get_mrs_word(int);
    void print_morse_msg();

};


class Ascii_Msg
{
    Morse_Msg* _mrs_msg;
    std::vector<std::string> _ascii_msg;

public:
    Ascii_Msg(Morse_Msg* mrs_msg); // constructor
    //Ascii_Msg(const Ascii_Msg& Ascii_Msg_Old){}; // copy constructor

    ~Ascii_Msg() {}; // destructor

    Ascii_Msg& operator = (const Ascii_Msg&);

    std::string mrs2ascii_word(std::string);
    std::string get_word(int);
    void print_ascii_msg();
};




#endif // ENCRYPTION_SCHEME_CLASSES_H
