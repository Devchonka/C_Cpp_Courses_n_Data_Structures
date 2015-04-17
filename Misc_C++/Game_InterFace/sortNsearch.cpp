#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp> // for password comparison
#include "validate.h"
#include "fileOperations.h"
#include "usrInterface.h"
#include "sortNsearch.h"

using namespace std;

void selectionSort(User* pUser, SortOrder order) // by USER_ID, TIME_STAMP, GAME 2,4,5
{
    int i, min_i, min_val1, min_val5, min_val6 ;
    string min_val2, min_val3;
    long long min_val4;

    int len = pUser ->gameList.size();

    for (i =0; i<len; i++)
    {
        min_i = i;
        min_val1 = pUser -> idList [i];
        min_val2 = pUser -> userIdList [i];
        min_val3 = pUser -> pwdList [i];
        min_val4 = pUser -> timeStampList [i];
        min_val5 = pUser -> gameList [i];
        min_val6 = pUser -> roleList [i];

        for (int index = i+1; index<len; index++)
        {
            if (sortType(order, pUser, min_val2, min_val4, min_val5, index))
            {
                min_val1 = pUser -> idList [index];
                min_val2 = pUser -> userIdList [index];
                min_val3 = pUser -> pwdList [index];
                min_val4 = pUser -> timeStampList [index];
                min_val5 = pUser -> gameList [index];
                min_val6 = pUser -> roleList [index];
                min_i = index;
            }
        }
        pUser -> idList [min_i] = pUser -> idList [i];
        pUser -> userIdList [min_i] = pUser -> userIdList [i];
        pUser -> pwdList [min_i] = pUser -> pwdList [i];
        pUser -> timeStampList [min_i] = pUser -> timeStampList [i];
        pUser -> gameList [min_i] = pUser -> gameList [i];
        pUser -> roleList [min_i] = pUser -> roleList [i];

        pUser -> idList [i] = min_val1;
        pUser -> userIdList [i] = min_val2;
        pUser -> pwdList [i] = min_val3;
        pUser -> timeStampList [i] = min_val4;
        pUser -> gameList [i] = min_val5;
        pUser -> roleList [i] = min_val6;
    }
}




int userSearch(string usrName, User* pUser)
{
    vector <string> copyVec = pUser->userIdList;
    transform(usrName.begin(), usrName.end(), usrName.begin(), ::tolower);
    int first =0,
        last = copyVec.size() - 1,
        mid,
        pos = -1;
    bool found = false;
    string loweredId;

    while (!found && first<=last)
    {
        mid = (first+last) / 2;
        loweredId = copyVec[mid];
        transform(loweredId.begin(), loweredId.end(), loweredId.begin(), ::tolower);

        if (loweredId == usrName)
        {
            found = true;
            pos = mid;
        }
        else if (loweredId > usrName)
            last = mid-1;
        else
            first = mid+1;
    }
    return pos;
}

bool sortType(SortOrder order, User* pUser, string min_val2, long long min_val4, int min_val5, int index)
{
    switch (order)
    {
    case SortOrder::USER_ID:
    {
        string strUsr = pUser -> userIdList [index];
        string strComp = min_val2;
        transform(strUsr.begin(), strUsr.end(), strUsr.begin(), ::tolower); // lower case string
        transform(strComp.begin(), strComp.end(), strComp.begin(), ::tolower);
        return (strUsr<strComp);
    }
    case SortOrder::TIME_STAMP:
        return (pUser -> timeStampList [index]<min_val4);
    case SortOrder::GAME:
        return (pUser -> gameList [index]<min_val5);
    }
}

void adminMenu(User* pUser)
{
    bool invalidEntry = true;
    int choice;
    do
    {
        cout<< "Please select the sorted order for the report: "<<endl;
        cout <<" \t1. By User ID"<<endl;
        cout <<" \t2. By Last Login Time"<<endl;
        cout <<" \t3. Game Console Preference"<<endl;
        cout <<" \t4. Exit"<<endl;
        cout << "Enter your choice:\t";
        cin>>choice;

        switch(choice)
        {
        case 1:
        {
            selectionSort(pUser, SortOrder::USER_ID);
            printLog(pUser);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            invalidEntry =false;
            break;
        }
        case 2:
        {
            selectionSort(pUser, SortOrder::TIME_STAMP);
            printLog(pUser);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            invalidEntry =false;
            break;
        }
        case 3:
        {
            selectionSort(pUser, SortOrder::GAME);
            printLog(pUser);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            invalidEntry =false;
            break;
        }
        case 4:
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            invalidEntry =false;
            break;
        }
        default:
        {
            printErrorMsg(Error::INVALID_SORT);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        }
    }
    while (invalidEntry);
}
