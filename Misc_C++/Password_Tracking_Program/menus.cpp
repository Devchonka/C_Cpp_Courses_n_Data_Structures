/**
 * @file menus.cpp
 * @brief  Functions:
    menu [Main menu contains choices for user to record passwords or view existing file]
    menuBrief [Brief menu that asks user if they want to see recorded passwords before exiting program]
    dateStamp [Returns current date]
    timeStamp [Returns current time]
*/

#include "Pass.h"
#include<iostream>
#include <ctime> // for date stamp
#include <string>
#include <cstdio> // for time stamp
#include<limits>
using namespace std;

void menuBrief()
{
    bool invalidEntry = true;
    int choice;

    do
    {
        cout<<"\n*************** BRIEF MENU ************"<<endl;
        cout<<"\nPlease pick a choice (1 or 2)"<<endl;
        cout<<"1)\tDisplay recorded passwords"<<endl;
        cout<<"2)\tExit without recording or displaying passwords"<<endl;
        cout<<"*****************************************"<<endl;
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"\nDisplaying recorded passwords\n";
            FileRead();
            invalidEntry =false;
            break;
        case 2:
            cout<<"\nExiting without displaying passwords\n";
            invalidEntry =false;
            break;
        default:
            cout<<"\nInvalid entry, please enter number 1 or 2"<<endl;
            invalidEntry =true;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    while (invalidEntry);
}

string dateStamp() // get current date
{
    char buffer[12]; //max month
    buffer[0] = '\0';
    time_t now = time(nullptr);
    strftime(buffer, 12, "%m/%d/%Y", localtime(&now));
    return buffer;
}

string timeStamp() // get current time
{
    char buffer [60]; //max time
    time_t now = time (&now);
    strftime (buffer,60,"%I:%M %p",localtime (&now));
    return buffer;
}

void menu(int* index)
{
    bool invalidEntry = true;
    int choice;

    do
    {
        cout<<"\n************* MAIN MENU *******************"<<endl;
        cout<<"Please enter your choice (1, 2, 3, or 4): "<<endl;
        cout<<"1)\tCreate new blank password file and enter passwords"<<endl;
        cout<<"2)\tAppend passwords to existing file"<<endl;
        cout<<"3)\tView existing password file"<<endl;
        cout<<"4)\tExit"<<endl;
        cout<<"*****************************************"<<endl;
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"\nCreated new blank password file to enter passwords\n"<<endl;
            createTxtFile(index); // create blank document
            EnterPasswords(index); // Append passwords to file, verify validity, record them
            menuBrief(); // ask whether user wants to see them displayed
            invalidEntry =false;
            break;
        case 2:
            cout<<"\nOpening existing password file to enter new passwords\n";
            EnterPasswords(index);
            menuBrief();
            invalidEntry =false;
            break;
        case 3:
            cout<<"\nOpening existing password file to display passwords\n";
            FileRead(); // Display passwords recorded
            invalidEntry =false;
            break;
        case 4:
            cout<<"\nExiting without recording or displaying passwords\n";
            invalidEntry =false;
            break;
        default:
            cout<<"\nInvalid entry, please enter number 1,2, or 3"<<endl;
            invalidEntry =true;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    while (invalidEntry);
}

int main()
{
    int index=1;
    menu(&index);
    return 0;
}
