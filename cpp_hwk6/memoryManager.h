#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include <memory>
#include <map>
#include <list>
#include <vector>
#include <iostream>

void* operator new(size_t);
void* operator new[](size_t);
void* operator new(size_t, int);
void operator delete(void*) throw();
void operator delete[](void*) throw();

class memoryManager // this is a singleton
{
private:
    int _numAllocations;
protected:
    static memoryManager* instance;
    memoryManager():_numAllocations(0) {};
public:
    ~memoryManager();
    std::map <void*, size_t> address2bytes;
    static memoryManager* getInstance();

    void increm_allocations();
    void decrem_allocations();
    void print_numAlloc();

};

class testClass
{
    std::vector<int*>* _vec;
public:
    testClass(int);
    ~testClass();
};

#endif // MEMORYMANAGER_H
