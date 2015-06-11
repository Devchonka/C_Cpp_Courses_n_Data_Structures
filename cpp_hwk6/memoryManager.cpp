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
    size_t bytes =0;
    for_each(address2bytes.begin(), address2bytes.end(), [&](pair<void*, size_t> val) { bytes+=val.second;});
    cout<<"Bytes Leaked in Program: "<< bytes<< endl; // After it's own deletion
    free_leaks();
}

void memoryManager:: free_leaks()
{
    cout << "Starting process to clear memory leaks."<<endl;
    for_each(address2bytes.begin(), address2bytes.end(), [&](pair<void*, size_t> val) {free(val.first);});
    cout<< " Leak Clearing Complete."<<endl;
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
    _vec = new std::vector<int*>;
    _list = new std::list<std::string*>;
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
    memMngr->address2bytes.insert(make_pair(ptr, st));
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
        auto ptr = memMngr->address2bytes.find(p);
        memMngr->address2bytes.erase(ptr->first);
        free(p);
        p=nullptr;
    }
}

void operator delete[](void* p) throw()
{
    if(p)
    {
        memoryManager* memMngr = memoryManager::getInstance();
        memMngr->decrem_allocations();
        auto ptr = memMngr->address2bytes.find(p);
        memMngr->address2bytes.erase(ptr->first);
        free(p);
        p= nullptr;
    }
}
