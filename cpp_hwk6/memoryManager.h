#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include <memory>
#include <map>
#include <list>
#include <vector>
#include <iostream>

class memoryManager // this is a singleton
{
private:
    int _numAllocations;
protected:
    static memoryManager* instance;
    memoryManager():_numAllocations(0),address2bytes() {};
public:
    ~memoryManager();
    std::map <void*, size_t> address2bytes;
    static memoryManager* getInstance();

    void increm_allocations();
    void decrem_allocations();
    void print_allocations();

};


class testClass
{
    std::vector<int*>* _vec;
    std::list<std::string*>* _list;

public:
    testClass(int, int);
    ~testClass();
    void* operator new(size_t); // the below are implicitly static if inside class
    void* operator new[](size_t);
    void* operator new(size_t, int);
    void operator delete(void*) throw();
    void operator delete[](void*) throw();
};


#endif // MEMORYMANAGER_H
