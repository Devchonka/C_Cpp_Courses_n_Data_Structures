/**
    Hashed dictionary implementation using an array.
    Implemented as a template, thus parameter for static array is passed in as an argument.
    Hashed table takes user-defined pointer function to input-specific hashing function.
    Collision resolution implemented using linked lists as the overflow area for synonyms given same hash table index.
*/

#ifndef HASHED_DICT_H
#define HASHED_DICT_H

#include <iomanip>
#include <iostream>
#include "singlyNode.h"
#include "validation.h"

/*******************************
   Class and method declarations.
********************************/
template <class keyT, class itemT>
class hashedDict
{
private:
    int _numCollisions;
    int _count;
    int _arSize;
    int* _LLsize;
    singlyNode<keyT, itemT>** _nodes;
protected:
    void _clearDict() const;

public:
    hashedDict(const int arSize): _numCollisions(0), _count(0), _arSize(arSize),
        _LLsize(new int[arSize]), _nodes(new singlyNode<keyT, itemT>*[arSize])
    {
        for (int i = 0; i< arSize; i++)
        {
            _nodes[i] = nullptr;
            _LLsize[i] = 0;
        }

    }
    ~hashedDict()
    {
        _clearDict();
    }
    bool addNode(const keyT&, const itemT&, unsigned int (*)(const keyT&));
    bool searchNode(const keyT&, unsigned int (*)(const std::string&));

    // Aids for statistics for hash table
    int getCount() const;
    int getColl() const;
    int getAveLLsize() const;
    int getMaxLLsize() const;
    float getLoadFac() const;
    int getNumLL() const;
    void printLLnum() const;
    void printHashed(bool) const;
};

/*******************************
   Method definitions.
********************************/

/**
    Getter functions for display of statistics:
    -Total number of elements stored in hash table and overflow area.
    -Number of collisions of synonyms with the same index for the hash table.
    -Load Factor (how full the actual array of elements is), not including linked lists.
    -Number of chains that contain at least 2 elements in the same hash dictionary index.
    -Ave linked list size.
    -Max linked list size.
    -Print size of all linked lists as they result in the hash table.

*/

template <class keyT, class itemT>
int hashedDict<keyT,itemT> ::  getCount() const
    {
        return _count;
    }

template <class keyT, class itemT>
int hashedDict<keyT,itemT> :: getColl() const
    {
        return _numCollisions;
    }

template <class keyT, class itemT>
float hashedDict<keyT,itemT> :: getLoadFac() const
    {
        return (float)(_count - _numCollisions)*100 / _arSize;
    }

template <class keyT, class itemT>
int hashedDict<keyT, itemT> :: getNumLL() const
{
    int numLL = 0;
    for (int i=0 ; i < _arSize; i++)
    {
        if (_LLsize[i] > 1)
            numLL++;
    }
    return numLL;
}

template <class keyT, class itemT>
int hashedDict<keyT,itemT>::getAveLLsize() const
{
    int sum =0, numLL =0;
    for (int i = 0; i<_arSize; i++)
        if (_LLsize[i] > 1)
        {
            numLL ++;
            sum += _LLsize[i];
        }
    if (numLL == 0)
        return 0;
    else
        return sum / numLL;
}

template <class keyT, class itemT>
int hashedDict<keyT,itemT>::getMaxLLsize() const
{
    int Max = _LLsize[0];
    for (int i = 1; i<_arSize; i++)
    {
        if (_LLsize[i] != 0 && _LLsize[i] > Max)
        {
            Max = _LLsize[i];
        }

    }
    return Max;
}


template <class keyT, class itemT>
void hashedDict<keyT,itemT>::printLLnum() const
{
    for (int i=0; i<_arSize; i++)
        std::cout<< _LLsize[i] << " ";
    std::cout<<std::endl;

}
/**
    Creates a node with provided item and key, obtains a hashed value using a function pointer provided,
    and inserts pointer to hash table that points to new node.
    Function returns true if added into hash, false if added into LL.
*/

template <class keyT, class itemT>
bool hashedDict<keyT, itemT>::addNode (const keyT& newKey, const itemT& newItem, unsigned int (*hashFuncPtr)(const keyT&))
{
    bool ableToHash = true;
    singlyNode<keyT, itemT>* newNode = new singlyNode <keyT, itemT> (newKey, newItem);
    int hashIndex = hashFuncPtr(newKey);

    if (_nodes[hashIndex] == nullptr)
        _nodes[hashIndex] = newNode;

    else
    {
        ableToHash = false;
        newNode->setFwd(_nodes[hashIndex]); // add newNode to front of LL
        _nodes[hashIndex] = newNode;
        _numCollisions++;
    }
    _LLsize[hashIndex]++;
    _count++;
    return ableToHash;
}

/**
    Takes in a search key and runs it through user-defined hashing function to get hash table index.
    Searches the hash at the given index, and searched the attached linked list in until it's found.
    Returns true if item is found, false otherwise.
*/

template<class keyT, class itemT>
bool hashedDict<keyT,itemT> :: searchNode(const keyT& searchKey, unsigned int (*hashFuncPtr)(const std::string&))
{
    int index = hashFuncPtr(searchKey);
    bool ableToFind = false;

    singlyNode<keyT, itemT>* searchPtr = _nodes[index];
    for (int i = 0; i < _LLsize[index]; i++)
    {
        if (searchPtr->getKey() != searchKey)
            searchPtr = searchPtr->getFwd();
        else
        {
            ableToFind = true;
            std:: cout << searchPtr->getItem() << " " << searchPtr->getKey()<<std::endl;
            break;
        }
    }
    if (!ableToFind)
        printErrorMsg(Error::BAD_SEARCH);
    return ableToFind;
}

/**
    Prints hash table, taking in bool variable indent.
    If indent is true, method prints the entries in an indented way showing hash index and whether it's in a linked list.
    If indent is false, method prints entires in a column in the order they're placed in the table.
*/
template <class keyT, class itemT>
void hashedDict<keyT,itemT>:: printHashed(bool indent) const
{
    for(int i = 0; i < _arSize; i++)
    {
        if (indent)
        {
            std::cout << "Index "<< i <<": ";
            if (_LLsize[i] == 0)
                std::cout << std::endl;
        }
        if (_LLsize[i] >0)
        {
            if (indent)
                std::cout<< std::right << std::setw(5);
            std::cout << _nodes[i]->getItem()<<std::endl;
            singlyNode<keyT,itemT>* nextNode = _nodes[i]->getFwd();
            while (nextNode)
            {
                if (indent)
                    std::cout<< std::right << std::setw(20);
                std::cout << nextNode->getItem() <<std::endl;
                nextNode = nextNode->getFwd();
            }
        }
    }
}

/**
    Function that clears hash table and associated linked lists.
    This protected method can be called only by destructor.
*/

template <class keyT, class itemT>
void hashedDict<keyT, itemT>::_clearDict() const
{
    for (int i =0; i< getCount(); i++)
        delete _nodes.at(i);
    delete _nodes;
}

#endif // HASHED_DICT_H
