/**
 * @file passOperations.cpp
 * @brief  Functions:
    createTxtFile [Creates a blank text document]
    EnterPasswords [Lets user input password candidate and calls VerifyPass to validate password by the rules before recording it]
    FileRead [Reads back to user recorded passwords in text file]
    get4Lines [Gets last 4 lines recorded in txt file]
    parsePass [Parses last 4 passwords so that password validity can be verified, also increments value pointer is at on pass index]
*/

#include "Pass.h"
#include<iostream>
#include<fstream>
#include<vector> // to store passwords
#include<string> // for password type
using namespace std;
const string filename = "Passwords_V2.txt"; // name of text file where passwords stored, global but const

int createTxtFile(int* index) //create new blank txt file
{
    ofstream writer (filename); //create ofstream object
    if (!writer)
    {
        cout<<"Error creating new file"<<endl;
        return -1;
    }
    writer.close(); //close written file
}

int EnterPasswords(int* index) //append to txt file
{
    ofstream appender(filename,ios::app);
    if(!appender)
    {
        cout<<"Error opening existing file to append to"<<endl;
        return -1;
    }

    string passCandidate;
    vector<string> pass;
    do // do...while loop that checks condition at end of code block
    {
        cout<<"\nEnter password (enter 0 to end)\t";
        cin>>passCandidate;
        if (passCandidate=="0")
        {
            break;
        }
        else
        {
            if (VerifyPass(passCandidate,index))
            {
                appender<<*index<<"\t"<<passCandidate<<"\t"<<timeStamp()<<"\t"<<dateStamp()<<endl;
                cout<<"Password Saved"<<endl;

            }
        }
    }

    while("passCandidate"!="0" ); // exit if '0' entered

    appender.close();
}

int FileRead()
{
    string line;
    ifstream reader(filename);
    if (!reader)
    {
        cout<<"Error opening file"<<endl; //what error tags?
        return -1;
    }


    {
        for(int i=0; ! reader.eof(); i++)
        {
            getline(reader,line);
            cout<<line<<endl;
        }
    }

    reader.close();
}
