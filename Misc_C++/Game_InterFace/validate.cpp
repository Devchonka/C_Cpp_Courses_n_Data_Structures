#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "validate.h"
#include "fileOperations.h"
#include "usrInterface.h"
#include "sortNsearch.h"

using namespace std;

bool validateCmdLineArgs(int argc, char** argv, string* filename, bool* admin)
{
    switch (argc)
    {
    case 1:
    case 2:
    {
        printErrorMsg(Error::WRONG_CMD_ARGS);
        return false;
    }
    case 3:
    {
        string argv1 = argv[1];
        string argv2 = argv[2];
        *filename = argv2;
        if (argv1 == "-datafile" && fExists(filename))
            return true;
        else
            {
                if (argv1!="-datafile")
                {
                    printErrorMsg(Error::WRONG_CMD_ARGS);
                    return false;
                }
                else if (!fExists(filename))
                {
                  printErrorMsg(Error::CORRUPT_FILE);
                  return false;
                }
            }
    }
    case 4:
    {
        string argv1 = argv[1];
        string argv2 = argv[2];
        string argv3 = argv[3];
        *filename = argv2;
        if (argv1 =="-datafile" && fExists(filename) && argv3 == "-admin")
        {
            *admin = true;
            return true;
        }
        else if (!fExists(filename))
        {
            printErrorMsg(Error::CORRUPT_FILE);
            return false;
        }
        else
        {
            printErrorMsg(Error::WRONG_CMD_ARGS);
            return false;
        }
    }
    default:
    {
        printErrorMsg(Error::WRONG_CMD_ARGS);
        return false;
    }
    }
}


bool validateUsrLogin(User* pUser, string userId, string pass, int* index)
{
    selectionSort(pUser, SortOrder::USER_ID);
    *index = userSearch(userId, pUser);

    if (*index == -1 || pUser -> pwdList[*index] != pass)
    {
        printErrorMsg(Error::WRONG_ID);
        return false;
    }
    else
        return true;
}

void printErrorMsg(Error msg)
{
    cout << ErrorTable[static_cast<int>(msg)] << endl;
}

bool fExists(const string* filename)
{
  ifstream ifile(*filename);
  return ifile;
}
