#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include <memory>
#include <map>
#include <list>
#include <vector>
#include <iostream>
#include <algorithm>

template<class T> class MallocAllocator {
public:
    typedef T value_type;
    MallocAllocator(){}
    template<class U> MallocAllocator(const MallocAllocator<U>& other){}
    T* allocate(size_t count){
        return (T*)malloc(count * sizeof(T));
    }
    void deallocate(T* object, size_t n){
        free(object);
    }
};

class memoryManager // this is a singleton
{
private:
    int _numAllocations;
protected:
    static memoryManager* instance;
    memoryManager():_numAllocations(),address2bytes() {};
public:
    ~memoryManager();
    std::map<void*, size_t,  std::less<void*>, MallocAllocator<std::pair<void*, size_t>>> address2bytes;
    static memoryManager* getInstance();

    void increm_allocations();
    void decrem_allocations();
    void print_allocations();

    void free_leaks();

    void* operator new(size_t st)
    {
        return malloc(st);
    }
};

class testClass
{
    std::vector<int*>* _vec;
    std::list<std::string*>* _list;
    int _n_vec_elem;
    int _n_list_elem;

public:
    testClass(int n1, int n2): _vec(nullptr), _list(nullptr), _n_vec_elem(n1), _n_list_elem(n2) {};
    void init();
    ~testClass();
};

void* operator new(size_t);
void* operator new[](size_t);
void* operator new(size_t, int);
void operator delete(void*) throw();
void operator delete[](void*) throw();

#endif // MEMORYMANAGER_H
