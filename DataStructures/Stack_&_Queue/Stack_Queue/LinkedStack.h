/**
 Linked (dynamic) implementation of a stack.
*/

#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include <iostream>
#include "singlyNode.h"
template<class T>
class LinkedStack
{
private:
    int _count;
    singlyNode<T>* _top;
public:
    LinkedStack(): _count(0), _top(nullptr) {};
    ~LinkedStack();
    T getTop() const;
    int getCount() const;
    bool isEmpty();
    bool push(const T);
    bool pop();
    bool pop(T&);
};

/**
 Destructor deletes all nodes from stack, which is all that was dynamically allocated.
*/
template<class T>
LinkedStack<T>:: ~LinkedStack()
{
    singlyNode<T>* currPtr = _top;
    singlyNode<T>* fwdPtr;
    while(currPtr)
    {
        fwdPtr = currPtr->getNodeF();
        delete currPtr;
        currPtr = fwdPtr;
    }

}

/**
 Returns a copy of the element at the top of the stack, essentially just peeking.
*/
template<class T>
T LinkedStack<T>::getTop() const
{
    if (_top == nullptr)
    {
        std::cerr << "Attempt to peek at an empty stack!" << std::endl;
        exit(1);
    }
    return _top->getNodeData();
}

/**
 Returns the number of elements present in the stack.
*/
template<class T>
int LinkedStack<T>::getCount() const
{
    return _count;
}

/**
 Returns true if stack has no elements, false otherwise.
*/
template<class T>
bool LinkedStack<T>::isEmpty()
{
    return (_count ==0);
}

/**
 Pushes a new node with the parameter data onto the top of the stack.
*/
template<class T>
bool LinkedStack<T>:: push(const T data)
{
    singlyNode<T>* insertPtr = new singlyNode<T>(data);
    bool ableToPush = insertPtr;
    if(ableToPush)
    {
        insertPtr->setNodeF(_top);
        _top = insertPtr;
        _count++;
        std::cout<<"Pushed "<<insertPtr->getNodeData()<<" on stack"<<std::endl;
    }
    return ableToPush;
}

/**
 Pops the top element of the stack, freeing the memory.
*/
template<class T>
bool LinkedStack<T>:: pop()
{
    bool ableToPop = !isEmpty();
    if (ableToPop)
    {
        std::cout<<"Popped "<<_top->getNodeData()<<" from stack"<<std::endl;
        singlyNode<T>* topF = _top->getNodeF();
        delete _top;
        _count--;
        _top = topF;
    }
    return ableToPop;
}

/**
 Pops the top element of the stack, freeing the memory.
 Changes the reference to show the item that was popped to caller function.
*/
template<class T>
bool LinkedStack<T>:: pop(T& data)
{
    bool ableToPop = !isEmpty();
    if (ableToPop)
    {
        data = _top->getNodeData();
        singlyNode<T>* topF = _top->getNodeF();
        delete _top;
        _count--;
        _top = topF;
        std::cout<<"Popped "<<data<<" from stack"<<std::endl;
    }
    return ableToPop;
}

#endif // LINKED_STACK_H
