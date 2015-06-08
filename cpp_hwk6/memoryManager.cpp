#include "memoryManager.h"

using namespace std;

memoryManager* memoryManager::instance = 0;

/**
    MemoryManager class function definitions.
*/
memoryManager* memoryManager:: getInstance() // note this is static in declaration
{
    if(instance == 0)
    {
        instance = new(1) memoryManager();
    }
    return instance;
}

memoryManager:: ~memoryManager()
{
    cout<<"Number of Allocations: "<< _numAllocations-1 << endl; // After it's own deletion
}

void memoryManager::increm_allocations()
{
    _numAllocations++;
}

void memoryManager::decrem_allocations()
{
    _numAllocations--;
}

void memoryManager::print_numAlloc()
{
    cout<<"Number of Allocations: " << _numAllocations<<endl;
}


testClass::testClass(int num_vec_elem)
{
    _vec = new vector<int*>;
    for (int i =0; i<num_vec_elem; ++i)
    {
        int* pInt = new int(1);
        _vec->push_back(pInt);
    }
}

testClass:: ~testClass()
{
    for(int i =_vec->size(); i>0; i--)
    {
        delete (*_vec)[i];
    }
    delete (_vec);
}

/**
    Overloaded new and delete functions
*/
void* operator new(size_t st)
{
    cout<<"GETTING NEW"<<endl;
    memoryManager* memMngr = memoryManager::getInstance();
    memMngr->increm_allocations();
    void* ptr = malloc(st);
    memMngr->address2bytes.insert(make_pair(ptr, st));
    cout<<"END OF  NEW"<<endl;
    return ptr;
}

void* operator new [](size_t st)
{
    memoryManager* memMngr = memoryManager::getInstance();
    memMngr->increm_allocations();
    void* ptr = malloc(st);
    memMngr->address2bytes.insert(make_pair(ptr, st));
    return ptr;
}

void* operator new(size_t st, int a)
{
    //number_of_allocations++;???
    return malloc(st * a);
}

void operator delete(void* p) throw()
{
    if (p)
    {
    memoryManager* memMngr = memoryManager::getInstance();
    memMngr->decrem_allocations();
    free(p);
    }
}

void operator delete[](void* p) throw()
{
    if (p)
    {
       memoryManager* memMngr = memoryManager::getInstance();
    memMngr->decrem_allocations();
    free(p);
    }

}
