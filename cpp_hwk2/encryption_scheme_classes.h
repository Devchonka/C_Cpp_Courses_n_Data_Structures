#ifndef ENCRYPTION_SCHEME_CLASSES_H
#define ENCRYPTION_SCHEME_CLASSES_H

#include <iostream>
#include <bitset>
#include <string>
#include <vector>

#include "Hashed_Dict.h"

class Binary_Msg
{
    std::vector< std::bitset<2> > _bin_msg;
    int _num_bits;

public:
    Binary_Msg(char*, int*); // constructor
    ~Binary_Msg(){}; // destructor

    std::bitset<2> get_bits(int);
    int get_num_bits();
    void print_bit_msg();
};


class Morse_Msg
{
    // hashedDict<std::string, char> _morse_table(int Size);
    Binary_Msg* _bin_msg;
    std::vector<std::string> _mrs_msg;


public:
    Morse_Msg(Binary_Msg*); // constructor
    Morse_Msg(const Morse_Msg&){}; // copy constructor
    ~Morse_Msg(){}; // destructor

    Morse_Msg& operator = (const Morse_Msg&);

    int get_num_words();
    std::string get_mrs(int);
    void print_morse_msg();
};


class Ascii_Msg
{
    Morse_Msg* _mrs_msg;
    std::vector<std::string> _ascii_msg;

public:
    Ascii_Msg(Morse_Msg* mrs_msg): _mrs_msg(mrs_msg){}; // constructor
    Ascii_Msg(const Ascii_Msg& Ascii_Msg_Old){}; // copy constructor

    ~Ascii_Msg(){}; // destructor

    Ascii_Msg& operator = (const Ascii_Msg&);

    std::string get_word(int);
    void print_ascii_msg();
};




#endif // ENCRYPTION_SCHEME_CLASSES_H
