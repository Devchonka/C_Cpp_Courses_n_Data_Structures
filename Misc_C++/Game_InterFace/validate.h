/**
 * @file validate.h
 * @brief  Function Declarations for all validation files and error logs.
    validateCmdLineArgs [Validates command line arguments]
    validateUsrLogin [Validates user log in]
    printErrorMsg [Prints out error message log]

*/

#ifndef VALIDATE_H // guard inclusions
#define VALIDATE_H

#include <iostream>
#include <vector>
#include <string>
#include "usrInterface.h"


enum class Error
{
    WRONG_ID, NOT_ADMIN, INVALID_SORT, NOT_USER, WRONG_CMD_ARGS, INVALID_PREF, CORRUPT_FILE, ERROR_COUNT
};

const char* const ErrorTable[ static_cast<int>(Error::ERROR_COUNT) ]  =
{
    "\n  Error: Wrong user ID or password.\n",
    "\n  Error: You are not authorized to access the reports.\n",
    "\n  Error: Invalid sorting method.\n",
    "\n  Error: Please call program as an admin.\n",
    "\n  Error: Wrong type or number of command line arguments. \n Please use format: ./GameInterface_V1 -datafile filename.txt [-admin]\n",
    "\n  Error: Invalid preference. \n Please enter choice 0, 1, 2, 3, 4, or <RETURN> to exit.\n",
    "\n  Error: Cannot open user log file.\n"
} ;

/**
 * Functions in validate.cpp
*/
bool validateCmdLineArgs(int, char**, std::string*, bool*);
bool validateUsrLogin(User* pUser,std::string, std::string, int*);
void printErrorMsg(Error);
bool fExists(const std::string*);

#endif /* VALIDATE_H */

