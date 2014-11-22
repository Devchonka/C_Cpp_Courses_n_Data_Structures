#ifndef SORTNSEARCH_H // guard inclusions
#define SORTNSEARCH_H

#include <string>
#include "usrInterface.h"

enum class SortOrder
{
    USER_ID, TIME_STAMP, GAME
};

void selectionSort(User*, SortOrder);
int userSearch(std::string, User*);
bool sortType(SortOrder, User*, std::string, long long, int, int);
void adminMenu(User*);

#endif /* SORTNSEARCH_H */
