/**
 @author Elena Menyaylenko
 CIS 22C HWK 3
 This program illustrates a basic text editor for line manipulation of text files.
 Data structure used is a template circular doubly linked list with one sentinel node at the head.
*/

#include <string>
#include "CircDoublyList.h"

void processCommand(CircDoublyList<std::string>*);
void populateList(CircDoublyList<std::string>*);


int main()

{
    CircDoublyList<std::string>* doubly = new CircDoublyList<std::string>;
    populateList(doubly);

    processCommand(doubly);

    delete doubly;
    return 0;
}
