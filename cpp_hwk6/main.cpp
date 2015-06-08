/**
    CIS 29 : Advanced C++.
    Author: Elena Menyaylenko           Date: 06/08/2015
    Assignment: New and Delete memory management by address and number of bytes.
    To compile code:
         g++ -std=c++11 *.h *.cpp -o cpp_hwk5
    To check memory leaks with Valgrind:
        valgrind --tool=memcheck --leak-check=yes ./cpp_hwk6
*/

#include <iostream>
#include "memoryManager.h"

using namespace std;

int main()
{
    // create some variables
    memoryManager* memMngr = memoryManager::getInstance();

    testClass* test = new testClass(1);

    memMngr->print_numAlloc();
    delete(test);
    delete(memMngr);

/*
    list<string*>* testList = new list<string*>(10);
    for (int i =0; i <3; ++i)
    {
        string* p = new string("hi");
        testList->push_back(p);
    }
    memMngr->print_numAlloc();
    delete(testList);
	memMngr->print_numAlloc();
	*/


	//memMngr->check_memLeaks();

    return 0;
}
