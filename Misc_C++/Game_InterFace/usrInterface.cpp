#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include "validate.h"
#include "fileOperations.h"
#include "usrInterface.h"
using namespace std;


void getUsrLogin(User* pUser, int* index)
{
    bool validEntry = false;
    string userId, password;
    do
    {
        cout<<"Please enter user ID:\t";
        cin>>userId;
        cout<<"Please enter password:\t ";
        cin>>password;
        cin.clear();
        validEntry = validateUsrLogin(pUser, userId, password, index);
    }
    while(!validEntry);
}

void getUsrPref(User* pUser, int* index, fstream& fileHandle, string* filename)
{
    bool invalidEntry = true;
    char choice;
    do
    {
        cout<<"\nYour current preference is "<<pUser -> gameList[*index]<<endl<<endl;
        cout<<"Please enter your new preference (0 /1/2/3/4) for (No Preference/Wii/Xbox/PlayStation/Other):\t";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        choice = cin.get();
        switch(choice)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        {
            pUser ->gameList[*index] = choice-'0';
            pUser ->timeStampList[*index] = time(nullptr);
            saveUsrChanges(fileHandle, pUser, filename);
            cout<<"Thank you. Your preference is saved (or unchanged). \n"<<endl;
            invalidEntry =false;
            break;
        }
        case '\n':
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            invalidEntry = false;
            break;
        }
        default:
        {
            cout<<ErrorTable[static_cast<int>(Error::INVALID_PREF)]<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        }
    }
    while (invalidEntry);
}
