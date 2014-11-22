/**
 * @file VerifyPass.cpp
 * @brief  Functions:
    VerifyPass [Verifies the 6 password rules are met, throws error with what to fix]
*/

#include "Pass.h"
#include<iostream>
#include<cctype>
#include<string>
#include<fstream>
using namespace std;
const string filename = "Passwords_V2.txt"; // name of text file where passwords stored, global but const

bool VerifyPass(string pass, int* index)
{
    bool goodLen = false,    // between 8-15 letters long
         goodLo = false,     //at least 1 lower case letter
         goodUp = false,     // at least 1 upper case letter
         goodDig = false,    // at least one digit
         goodSpec = true,   // no special characters
         goodVar = true;    // variety of passwords: last 4 are different

    int len= pass.length();

    if (len>7 && len<16)
        goodLen = true;
    else
        cout<<"\n\tPassword needs to be at least 8 and no more than 15 characters long "<<endl;

    // now traverse through string to flip other flags if encounter qualifier
    for ( int i = 0 ; pass[i] ; ++i )
    {
        if ( isupper(pass[i]) )
            goodUp = true ;             // upper case letter
        if ( islower(pass[i]) )
            goodLo = true ;             // lower case letter
        if ( isdigit(pass[i]) )
            goodDig = true ;            // digit
        if (pass.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789@-_.")!= std::string::npos)
            goodSpec = false ;          // special chars
    }

    vector <string> a=get4Lines();
    if (!a.empty()){
        vector <string> last4passwords=parsePass(a, index);
        for (int i=0; i<last4passwords.size()-1; i++)
        {
            if (pass.compare(last4passwords[i])==0) // if current pass is same as one of last 4
            {
                cout <<"\n\tPassword cannot be the same as last 4 passwords"<<endl;
                goodVar = false;
                break;
            }
        }
    }
    if (goodLo==false) cout <<"\n\tPassword needs at least one lower case letter"<<endl;
    if (goodUp==false) cout <<"\n\tPassword needs at least one upper case letter"<<endl;
    if (goodDig==false) cout <<"\n\tPassword needs at least one digit"<<endl;
    if (goodSpec==false) cout <<"\n\tPassword cannot have any special characters besides @,-,_, or ."<<endl;

    if ( goodLen && goodLo && goodUp && goodDig && goodSpec && goodVar)
        return true;
    else
        return false ;
}

vector<string> get4Lines()
{
    string line;
    ifstream reader(filename);
    if (!reader)
    {
        cout<<"Error opening file"<<endl; //what error tags?
    }
    int numLines=0, lineNeeded = 0;
    vector <string> last4Lines;
    for(int i=0; ! reader.eof(); i++)
    {
        getline(reader,line);
        numLines++;
    }
    if (numLines<4)
    {
        lineNeeded = 0;
    }
    else lineNeeded = numLines-4;
    numLines = 0;
    reader.close();
    ifstream reader2(filename);
    while (!reader2.eof())
    {
        getline(reader2, line);
        if (line.empty())
            break;
        numLines++;
        if (lineNeeded <= numLines)
        {
            last4Lines.push_back(line);
        }
    }
    reader2.close();
    return last4Lines;
}

vector <string> parsePass(vector<string> last4Lines, int* index)
{
    vector<string> last4Pass;
    for (int line=0; line<last4Lines.size(); line++)
    {
        int found1=last4Lines[line].find("\t");
        if (found1==string::npos)
        {
            last4Pass.resize(0);
            break;
        }
        int found2=last4Lines[line].find("\t",found1+1);
        if (found2==string::npos)
        {
            last4Pass.resize(0);
            break;
        }
        last4Pass.push_back(last4Lines[line].substr(found1+1,found2-found1-1)); //grab the password, store in last4Pass
        if (line==last4Lines.size()-1)
        {
            string val =last4Lines[line].substr(0,found1);
            int v = atoi(val.c_str()); // cast string to int
            *index = v+1; // changes value at location to which pointer is set
        }
    }
    return last4Pass;
}
