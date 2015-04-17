/**
 * @file Pass.h
 * @brief  Functions Declarations
    createTxtFile [Creates a blank text document]
    EnterPasswords [Lets user input password candidate and calls VerifyPass to validate password by the rules before recording it]
    FileRead [Reads back to user recorded passwords in text file]
    get4Lines [Gets last 4 lines recorded]
    parsePass [Parses each of last 4 lines to get the password]
*/

#ifndef PASS_H // guard inclusions
#define PASS_H

#include<string> // for password type
#include<vector>
using namespace std;

/**
 * Files in menus.cpp
*/
void menu(int*);
void menuBrief();
string dateStamp();
string timeStamp();

/**
 * Files in passOperations.cpp
*/
int createTxtFile(int*);
int EnterPasswords(int*);
int FileRead();

/**
 * Files in VerifyPass.cpp
*/
bool VerifyPass(string, int*);
vector<string> get4Lines();
vector <string> parsePass(vector<string>, int*);
bool isEnglish(char let);

#endif /* PASS_H */
