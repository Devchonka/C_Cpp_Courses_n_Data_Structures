/**
 * @author Elena Menyaylenko
 * @file main.cpp in project GameInterface_V1.cbp
 * @brief Game user interface for updating preferences for users and displaying sorted logs for admin
 * @version 1.0
 * @since 07/16/2014

 call to function: ./GameInterface_V1 -datafile UsrData.txt [-admin]

*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "validate.h"
#include "fileOperations.h"
#include "usrInterface.h"
#include "sortNsearch.h"

using namespace std;


int main(int argc, char** argv)
{
    fstream fileHandle;
    int usrIndex = 0;
    bool UsrAdmin = false, // admin bool from file log
         CmdAdmin = false,  // admin bool from command line arg
         trueAdmin = false;
    string filename;

    if (validateCmdLineArgs(argc, argv, &filename, &CmdAdmin))
    {
        User* pUser = readDatafile(fileHandle, &filename, &UsrAdmin);

        selectionSort(pUser, SortOrder::USER_ID);
        getUsrLogin(pUser, &usrIndex);
        UsrAdmin = pUser ->roleList[usrIndex];

        if (CmdAdmin && UsrAdmin)
        {
            adminMenu(pUser);
        }
        else if (CmdAdmin && !UsrAdmin)
        {
            printErrorMsg(Error::NOT_ADMIN);
        }
        else if (UsrAdmin && !CmdAdmin)
        {
            printErrorMsg(Error::NOT_USER);
        }
        else if (argc == 3)
        {
            getUsrPref(pUser, &usrIndex, fileHandle, &filename);
        }

        fileHandle.close();
        delete pUser;
    }
    return 0;
}
