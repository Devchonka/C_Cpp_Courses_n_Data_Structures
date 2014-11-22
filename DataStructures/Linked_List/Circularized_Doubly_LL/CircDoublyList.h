/**
 @author Elena Menyaylenko
 CIS 22C HWK 3
 This is the template header file for a circular doubly linked list.
*/

#ifndef CDBLLL_H
#define CDBLLL_H

#include <iomanip>
#include <iostream>

/*****************************************************
   Class and Method Declarations
*****************************************************/

/**
    This function creates the node class to be used in the linked list.
*/
template <class T>
class doublyNode
{
public: // all fields must be public since node fields must be accessible by list
    T _line;
    doublyNode* _fwd;
    doublyNode* _bck;

    doublyNode (): _line(" "), _fwd(nullptr), _bck(nullptr) {}; // default constructor (for dummy node)
    doublyNode (T line): _line(line), _fwd(nullptr), _bck(nullptr) {}; // regular node constructor
};

/**
    This function creates the circular doubly linked list class.
*/
template <class T>
class CircDoublyList
{
private:
    doublyNode<T>* _head; // node which points to head of list
    int _count; // number of items in list (without sentinel)
    doublyNode<T>* getPtr (int) const;
public:
    CircDoublyList();
    ~CircDoublyList();

    int getCount() const;
    bool isEmpty() const;
    bool insertNode(T, int);
    bool deleteNode(int);
    bool swapNode(int,int);
    doublyNode<T>* getHead() const;
    bool displayList(int, int) const;
};

/*****************************************************
   Method Definitions
*****************************************************/

/**
 Constructor for Linked List.
 Creates a dummy node at the head.
*/
template <class T>
CircDoublyList<T>:: CircDoublyList()
{
    // create dummy at the head and set its pointer
    doublyNode<T>* dummyHead = new doublyNode<T>;
    _head = dummyHead;

    dummyHead->_fwd = dummyHead;
    dummyHead->_bck = dummyHead;

    _count = 0; // set counter of list nodes to zero
}

/**
 Destructor for Linked List.
 Loop to destroy all remaining nodes by count of items left.
*/
template <class T>
CircDoublyList<T>::~CircDoublyList()
{
    doublyNode<T>* delPtr = _head->_fwd->_fwd; // delete the one behind you
    while (_count)
    {
        delete delPtr->_bck;
        delPtr = delPtr->_fwd;
        _count--;
    }
}

/**
 Returns number of items stored in linked list.
*/
template <class T>
int CircDoublyList<T>::getCount() const
{
    return _count;
};

/**
 Returns True if list only has sentinel node, False if count is greater than zero.
*/
template <class T>
bool CircDoublyList<T>::isEmpty() const
{
    return _count == 0;
};

/**
 Returns pointer to the node specified at position pos.
*/
template <class T>
doublyNode<T>* CircDoublyList<T>:: getPtr (int pos) const// make sure position valid
{
    doublyNode<T>* Ptr = _head;
    if (pos > 0 && pos <= _count)
    {
            for (int i = 0; i < pos; i++)
            Ptr = Ptr->_fwd;
    } // else returns head
    return Ptr;
}

/**
 Inserts new node with data provided by line, into position pos.
*/
template <class T>
bool CircDoublyList<T>:: insertNode(T line, int pos) // inserts node to given pos
{
    bool ableToInsert = (pos>0) && (pos <= _count+1);

    if (ableToInsert)
    {
        doublyNode<T>* newNode = new doublyNode<T>(line); // create node
        newNode->_line = line;
        doublyNode<T>* insertPtr = getPtr (pos);

        insertPtr->_bck->_fwd = newNode;
        newNode->_bck = insertPtr->_bck;
        insertPtr->_bck = newNode;
        newNode->_fwd = insertPtr;

        _count++;
    }
    return ableToInsert;
}

/**
 Deletes node at position pos.
*/
template <class T>
bool CircDoublyList<T>:: deleteNode(int pos)
{
    bool ableToDelete = (pos>0) && (pos <= _count);

    if (ableToDelete)
    {
        doublyNode<T>* delPtr = getPtr (pos);
        delPtr->_fwd->_bck = delPtr->_bck;
        delPtr->_bck->_fwd = delPtr->_fwd;
        delete delPtr;
        _count--;
    }
    return ableToDelete;
}

/**
 Prints out list entries, inclusively, from 'from' to 'to'.
*/
template <class T>
bool CircDoublyList<T>:: displayList(int from, int to) const
{
    bool ableToPrint = (from > 0 && from <=_count);
    if (ableToPrint)
    {
        doublyNode<T>* currPtr = getPtr(from);
        std::cout << std::setw(6) << std::left << "\nLine" << std::setw(70) << std::left << "Text" << std::endl;

        if (from <= to) // loop one direction if from <= to
        {
            while (from <= to)
            {
                std::cout << std::setw(6) << std::left << from++ <<std::setw(70) << std::left <<  currPtr->_line << std::endl;
                currPtr = currPtr->_fwd;
            }
        }
        else
        {
            while (from >= to) // loop other direction if from > to
            {
                std::cout << std::setw(6) << std::left << from-- <<std::setw(70) << std::left <<  currPtr->_line << std::endl;
                currPtr = currPtr->_bck;
            }
        }
    }
    return ableToPrint;
}

/**
 Returns pointer head of the list (otherwise a private member).
*/
template <class T>
doublyNode<T>* CircDoublyList<T>:: getHead() const
{
    return _head;
}

/**
 Swaps the two nodes with positions given by p1, p2.
 The function sets 4 temporary pointers to p1, p2, and the back of p1 and p2 (then, resetting one to the front of p1).
*/
template <class T>
bool CircDoublyList<T>:: swapNode(int p1,int p2)
{
    bool ableToSwap = (p1 > 0 && p2>0 && p1 <=_count && p2<=_count && p1 != p2);
    if (ableToSwap)
    {

        doublyNode<T>* pos1Ptr = getPtr(p1);
        doublyNode<T>* pos2Ptr = getPtr(p2);

        doublyNode<T>* pos1Tmp = pos1Ptr->_bck;
        doublyNode<T>* pos2Tmp = pos2Ptr->_bck;

        pos1Tmp->_fwd = pos2Ptr;
        pos1Ptr->_fwd->_bck = pos2Ptr;
        pos2Tmp->_fwd = pos1Ptr;
        pos2Ptr->_fwd->_bck = pos1Ptr;

        pos1Ptr->_bck = pos2Tmp;
        pos2Ptr->_bck = pos1Tmp;

        pos1Tmp = pos1Ptr->_fwd;

        pos1Ptr->_fwd = pos2Ptr->_fwd;
        pos2Ptr->_fwd = pos1Tmp;

    }
    return ableToSwap;
}

#endif // CDBLLL_H
