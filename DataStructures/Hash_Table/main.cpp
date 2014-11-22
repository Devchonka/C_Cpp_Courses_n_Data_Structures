#include <iostream>
#include <cstring>
#include <fstream>

#include "singlyNode.h"
#include "hashedDict.h"
#include "validation.h"
using namespace std;

const string FNAME = "academy_award_films.txt";
const int HASH_SIZE = 31;

bool populateHash(hashedDict<string, int>*);
void processCommand(hashedDict<string, int>*);
void help();

int main()
{
    hashedDict<string,int>* hashTable = new hashedDict<string,int>(HASH_SIZE);
    populateHash(hashTable);
    help();
    processCommand(hashTable);
    return 0;
}

/**
    Prints error in validation.h
*/
void printErrorMsg(Error msg)
{
    cout << ErrorTable[static_cast<int>(msg)] << endl;
}

/**
    Validated whether user input is valid.
*/
bool validChoice(string choice)
{
    string allowable = "SDPTMQ";
    if (choice.size()==1 && (allowable.find(toupper(choice[0])) != std::string::npos))
        return true;
    else
    {
        printErrorMsg(Error::BAD_INPUT);
        return false;
    }
}

/**
    Hashing function using the rotating hashing algorithm. It folds internal state and combines it with each
    byte of input, to give better LL distribution.
*/
unsigned int hashMap(const string& key)
{
    unsigned len = key.size()+1;
    char Key[len];
    strcpy(Key,key.c_str());

    unsigned h = 0, i = 0;

    for ( i = 0; i < len; i++ )
        h = ( h << 4 ) ^ ( h >> 28 ) ^ Key[i]*3;


    return h % HASH_SIZE;
}

/**
    Displays the menu for user.
*/
void help()
{
    int w1 = 10, w2 = 10;
    cout<< endl;
    cout << setw(w1) << left << "S: " << setw(w2) << left << "Search by a unique key (movie title)" << endl;
    cout << setw(w1) << left << "D: " <<  setw(w2) << left << "Display hash table contents in a column"<< endl;
    cout << setw(w1) << left << "P: " <<  setw(w2) << left << "Display hash table contents in an indented list"<< endl;
    cout << setw(w1) << left << "T: " <<  setw(w2) << left << "Show hash table statistics"<< endl;
    cout << setw(w1) << left << "M: " <<  setw(w2) << left << "Show menu"<< endl;
    cout << setw(w1) << left << "Q: " <<  setw(w2) << left << "Quit"<<endl;
}

/**
    Builds hash from input file. Returns false and prints error if file not found.
*/
bool populateHash(hashedDict<string, int>* hashTable)
{
    ifstream fileHandle;
    fileHandle.open(FNAME);

    bool ableToPopulate = fileHandle.good();
    if (ableToPopulate)
    {
        unsigned int (*hashFuncPtr)(const string&) = hashMap;
        string line =" ", name = " ";
        int year =0;

        while (getline(fileHandle, line))
        {
            year = stoi(line.substr(0,4));
            name = line.substr(5);
            hashTable->addNode(name, year, hashFuncPtr);
        }
        fileHandle.close();
    }
    else
        printErrorMsg(Error::BAD_IFILE);
    return ableToPopulate;
}

/**
    Processes user command for the hash table entries.
*/
void processCommand(hashedDict<string, int>* hashTable)
{
    unsigned int (*hashFuncPtr)(const string&) = hashMap;

    bool inProgress = true;
    while (inProgress)
    {
        string choice;
        do
        {
            cout<<" >> ";
            getline(cin, choice);
        }
        while (!validChoice(choice));
        switch (toupper(choice[0]))
        {
        case 'S':
        {
            string key = " ";
            cout << "Please enter key to search: ";
            getline(cin, key);
            hashTable->searchNode(key,hashFuncPtr);
            break;
        }
        case 'D':
        {
            hashTable->printHashed(false);
            break;
        }
        case 'P':
        {
            hashTable->printHashed(true);
            break;
        }
        case 'T':
        {
            cout<< "_____Hash table statistics____"<<endl;
            cout<<"Total entries stored: " << hashTable->getCount()<<endl;
            cout<<"Number of collisions: " << hashTable->getColl()<<endl;
            cout<<"Load factor: " << setprecision(3)<< hashTable->getLoadFac()<<endl;
            cout << "Number of linked lists: " << hashTable->getNumLL()<<endl;
            cout<<"Length of longest linked list: " << hashTable->getMaxLLsize()<<endl;
            cout<<"Ave number of nodes stored in linked list: " << hashTable->getAveLLsize()<<endl;
            cout<<"Number of nodes in each linked list: " << endl;;
            hashTable->printLLnum();
            break;
        }
        case 'M':
        {
            help();
            break;
        }
        case 'Q':
            inProgress = false;
        }

    }
}
