#include "encryption_scheme_classes.h"
#include <bitset>
#include <cstring>

using namespace std;

bool populateHash(hashedDict<string, char>&);

/****************************
Binary_Msg Method Definitions
*****************************/
Binary_Msg::Binary_Msg(char* char_bitsArray, int* num_chars): _num_bits(*num_chars * 8)
{
    std::bitset<8> char_in_bits;
    while(*char_bitsArray)
    {
        char_in_bits = *char_bitsArray;
        for(int i =0; i < 8; i=i+2)
        {
            std::bitset<2> bit_pair;
            bit_pair[i] = char_in_bits[i];
            bit_pair[i+1] = char_in_bits[i+1];
            _bin_msg.push_back(bit_pair);
            //std::cout<<bit_pair<<std::endl;
        }
        char_bitsArray++;
    }
}

int Binary_Msg:: get_num_bits()
{
    return _num_bits;
}

bitset<2> Binary_Msg:: get_bits(int index)
{
    return _bin_msg[index];
}

void Binary_Msg:: print_bit_msg()
{
    int Size = _bin_msg.size();
    int i =0;
    while(i<Size)
    {
        cout<<_bin_msg[i++];
    }
    cout<<endl;
}

/****************************
Morse_Msg Method Definitions
*****************************/
Morse_Msg:: Morse_Msg(Binary_Msg* bin_msg): _bin_msg(bin_msg), morse_table(hashedDict<string, char> (HASH_SIZE))
{
    // build morse look up table
    populateHash(morse_table);
    // build words vector in morse code
    int num_bit_pairs = _bin_msg->get_num_bits() / 2;
    int i=0;
    string word = " ";
    while(i < num_bit_pairs)
    {
        bitset<2> curr_bitset = bin_msg->get_bits(i);
        if(curr_bitset.none())   // 00 case
        {
            word.append(" ");
        }
        else if(curr_bitset.all())   // 11 case
        {
            _mrs_msg.push_back(word);
            word = " ";
        }
        else if(curr_bitset[0]==1)  // 10 case
        {
            word.append(".");
        }
        else  //01 case
        {
            word.append("-");
        }
        i+=2;
    }
}

string Morse_Msg:: get_mrs_word(int i)
{
    return _mrs_msg[i];
}

int Morse_Msg:: get_num_words()
{
    return _mrs_msg.size();
}


void Morse_Msg:: print_morse_msg()
{
    int Size = _mrs_msg.size();
    int i =0;
    while(i<Size)
    {
        cout<<_mrs_msg[i++];
    }
    cout<<endl;
}


/****************************
Ascii_Msg Method Definitions
*****************************/
Ascii_Msg:: Ascii_Msg(Morse_Msg* mrs_msg): _mrs_msg(mrs_msg)
{
    // build words vector in ascii code
    int i=0;
    int num_words = _mrs_msg->get_num_words();
    while(i < num_words)
    {
        string morse_word = _mrs_msg->get_mrs_word(i);
        string ascii_word = mrs2ascii_word(morse_word);
        _ascii_msg.push_back(ascii_word);
        i++;
    }
}

string Ascii_Msg::mrs2ascii_word(string morse_word)
{
    // split word to letters by spaces between dots and dashes
    string delimiter = " ";
    size_t pos = 0;
    string mrs_letter;
    while((pos = morse_word.find(delimiter)) != string::npos)
    {
        mrs_letter = morse_word.substr(0, pos);
        cout << mrs_letter << endl;
        //unsigned int (*hashFuncPtr)(const string&) = hashMap;
        //_mrs_msg->morse_table.searchNode(mrs_letter, hashFuncPtr);
        morse_word.erase(0, pos + delimiter.length());
    }


}





