/**
 * @file fileOperations.h
 * @brief  Function Declarations for file operations.
    readDatafile [Populates structs with current user entries]
    saveUsrChanges [Saves user preferences in re-writing file]
*/

#ifndef FILEOPERATIONS_H // guard inclusions
#define FILEOPERATIONS_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "usrInterface.h"

/**
 * Functions in fileOperations.cpp
*/
User* readDatafile(std::fstream&, std::string*, bool*);
void saveUsrChanges(std::fstream&, User*, std::string*);
void printLog(User*);

#endif /* FILEOPERATIONS_H */


