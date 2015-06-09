#include "memoryManager.h"

using namespace std;

memoryManager* memoryManager::instance = nullptr;
/**
    MemoryManager class function definitions.
*/
memoryManager* memoryManager:: getInstance() // note this is static in declaration
{
    if(instance == 0)
    {
        instance = new memoryManager();
    }
    return instance;
}

memoryManager:: ~memoryManager()
{
    cout<<"DESTRUCTOR: Number of Allocations: "<< _numAllocations << endl; // After it's own deletion
}

void memoryManager::increm_allocations()
{
    _numAllocations++;
}

void memoryManager::decrem_allocations()
{
    _numAllocations--;
}

void memoryManager::print_allocations()
{
    cout<<"Number of Allocations: " << _numAllocations<<endl;
    for(auto it = address2bytes.cbegin(); it != address2bytes.cend(); ++it)
    {
        cout<<"Pointer address: " << it->first<<"               # bytes: "<<it->second<<endl;
    }
}


void testClass::init()
{
    cout<<"HI"<<endl;
    _vec = new std::vector<int*>;
    cout<<"HI"<<endl;
    _list = new std::list<std::string*>;
    cout<<"HI"<<endl;
    // vector
    int* pInt = new int;
    for(int i =0; i<_n_vec_elem; ++i)
    {
        int* pInt = new int;
        _vec->push_back(pInt);
    }
    // list
    for(int i =0; i <_n_list_elem; ++i)
    {
        string* p = new string("hi");
        _list->push_back(p);
    }
}

testClass:: ~testClass()
{
    for(int i =_vec->size(); i>0; i--)
    {
        delete(*_vec)[i];
    }
    for(int i =_list->size(); i>0; i--)
    {
        //delete (_list->front());
    }
    delete(_vec);
    delete(_list);
}

/**
    Overloaded new and delete functions
*/
void* operator new(size_t st)
{
    memoryManager* memMngr = memoryManager::getInstance();
    memMngr->increm_allocations();
    void* ptr = malloc(st);
    mem_pair mp(ptr, st);
    memMngr->address2bytes.insert(mp);
    //memMngr->address2bytes.insert(make_pair(ptr, st));
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
    memoryManager* memMngr = memoryManager::getInstance();
    memMngr->increm_allocations();
    void* ptr = malloc(st);
    memMngr->address2bytes.insert(make_pair(ptr, st));
    return ptr;
}

void operator delete(void* p) throw()
{
    if(p)
    {
        memoryManager* memMngr = memoryManager::getInstance();
        memMngr->decrem_allocations();
        free(p);
    }
}

void operator delete[](void* p) throw()
{
    if(p)
    {
        memoryManager* memMngr = memoryManager::getInstance();
        memMngr->decrem_allocations();
        free(p);
    }
}
