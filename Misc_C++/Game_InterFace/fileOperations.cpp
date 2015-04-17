#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include "validate.h"
#include "fileOperations.h"
#include "usrInterface.h"
using namespace std;

User* readDatafile(fstream &fileHandle, string* pFilename, bool* pAdmin)
{
    User* pUser=new User;

    int idListT; // T for temporary variable
    string userIdListT;
    string pwdListT;
    long long timeStampListT;
    int gameListT;
    int roleListT;

    fileHandle.open(*pFilename, fstream::in | fstream::out);

    while (fileHandle>> idListT) // check to see that string is valid, not '\n'
    {
        pUser -> idList.push_back(idListT);
        fileHandle >> userIdListT;
        pUser -> userIdList.push_back(userIdListT);
        fileHandle >> pwdListT;
        pUser -> pwdList.push_back(pwdListT);
        fileHandle >> timeStampListT;
        pUser -> timeStampList.push_back(timeStampListT);
        fileHandle >> gameListT;
        pUser -> gameList.push_back(gameListT);
        fileHandle >> roleListT;
        pUser -> roleList.push_back(roleListT);
    }

    pUser ->admin = *pAdmin;
    return pUser;
}

void saveUsrChanges(fstream &fileHandle, User* pUser, string* pFilename)
{
    fileHandle.close();
    ofstream handle;
    handle.open(*pFilename);
    int len = pUser->idList.size();
    int i = 0;
    while(i < len)
    {
        handle << pUser-> idList[i]<<"\t"<<pUser-> userIdList[i]<<"\t"
                   << pUser-> pwdList[i]<<"\t"<<pUser-> timeStampList[i]<<"\t"
                   << pUser-> gameList[i]<<"\t"<<pUser-> roleList[i]<<"\n";
        i++;
    }
    handle.close();
}


void printLog(User* pUser)
{
    int len = pUser->gameList.size();
    int i=0;
    while(i < len)
    {
        cout << setw(15)<<left<< pUser-> idList[i]<<setw(15)<<left<<pUser-> userIdList[i]<<setw(15)<<left
             << pUser-> pwdList[i]<<setw(15)<<left<<pUser-> timeStampList[i]<<setw(15)<<left
             << pUser-> gameList[i]<<setw(15)<<left<<pUser-> roleList[i]<<"\n";
        i++;
    }
}
