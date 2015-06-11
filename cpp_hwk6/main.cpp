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
    memoryManager* memMngr = memoryManager::getInstance();
    testClass* test = new testClass(10, 0);
    test->init();
    memMngr->print_allocations();
    delete(test);
    delete(memMngr);
    return 0;
}
