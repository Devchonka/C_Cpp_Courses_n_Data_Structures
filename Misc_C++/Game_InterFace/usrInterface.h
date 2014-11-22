/**
 * @file usrInterface.h
 * @brief  Function Declarations for user selection updates to txt file.
    getUsrLogin[Obtains user login info]
    menu [Prompts user with options]
    adminSort [Sorts entries depending on admin's selection]
*/

#ifndef USRINTERFACE_H // guard inclusions
#define USRINTERFACE_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

/**
 * Functions in usrInterface.cpp
*/

struct User
{
    bool admin;
    std::vector <int> idList;
    std::vector <std::string> userIdList;
    std::vector <std::string> pwdList;
    std::vector <long long> timeStampList;
    std::vector <int> gameList;
    std::vector <int> roleList;
};


void getUsrLogin(User*, int*);
void getUsrPref(User*, int*, std::fstream&, std::string*);

#endif /* USRINTERFACE_H */
