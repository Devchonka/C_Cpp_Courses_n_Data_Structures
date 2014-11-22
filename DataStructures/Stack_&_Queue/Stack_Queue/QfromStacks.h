/**
 Linked (dynamic) implementation of a queue made up of using 2 stacks.
 Implementation based on taking advantage of queues being a FIFO structure, and stacks being a LIFO one.
 There is a newest stack which initially flips the element order, and a second stack which flips them again to
 mimic a queue ordering. Shift function helps flip elements from newest to oldest stack.
 Implemented using "lazy" approach where elements reside in newest stack until they must be shifted to oldest.
*/

#ifndef Q_FROM_STACKS_H
#define Q_FROM_STACKS_H

#include "LinkedStack.h"

template <class T>
class QfromStacks
{
private:
    LinkedStack<T>* _newest;
    LinkedStack<T>* _oldest;
    int _count;
    bool shiftElements();

public:
    QfromStacks();
    ~QfromStacks();
    bool isEmpty() const;
    int getCount() const;
    T getFront();
    bool enqueue(const T);
    bool dequeue();
    bool dequeue(T&);
};

/**
 Constructor sets the private member variable pointers to their respective new stacks, after calling their constructors.
*/
template <class T>
QfromStacks<T>::QfromStacks()
{
    _newest = new LinkedStack<T>();
    _oldest = new LinkedStack<T>();
    _count = 0;
}

/**
 Destructor calls destructors of both stacks, and then deletes the dynamically allocated pointers to each stack.
*/
template <class T>
QfromStacks<T>::~QfromStacks()
{
    _newest->~LinkedStack();
    _oldest->~LinkedStack();
    delete _newest;
    delete _oldest;
}

/**
 Shifts all elements from oldest stack to newest stack.
*/
template <class T>
bool QfromStacks<T>::shiftElements()

{
    bool ableToShift = _oldest->isEmpty();
    if (ableToShift)
    {
        T data;
        while (!_newest->isEmpty())
        {
            _newest->pop(data);
            _oldest->push(data);
        }

    }
    return ableToShift;
}

/**
 Returns true if both stacks are empty, false otherwise.
*/
template <class T>
bool QfromStacks<T>::isEmpty() const
{
    return (_newest->isEmpty() && _oldest->isEmpty());
}

/**
 Returns number of elements in data structure.
*/
template <class T>
int QfromStacks<T>::getCount() const

{
    return _newest->getCount()+_oldest->getCount();
}

/**
 Returns element that should be at the front of this imitation of a queue.
 It first needs to flip element order by shifting elements from one stack to another.
 Unlike regular queue, this function cannot be const since it requires a shifting of elements within stacks.
*/
template <class T>
T QfromStacks<T>::getFront()
{
    shiftElements();
    return _oldest->getTop();
}

/**
 Emulates enqueue function of queue by pushing elements onto newest stack.
*/
template <class T>
bool QfromStacks<T>::enqueue(const T data)
{
    return _newest->push(data);
}

/**
 Emulates dequeue function of queue by first popping elements from oldest stack, and
 pushing them onto newest stack.
*/
template <class T>
bool QfromStacks<T>::dequeue()
{
    shiftElements();
    return _oldest->pop();
}

/**
 Emulates dequeue function of queue by first popping elements from oldest stack, and
 pushing them onto newest stack. Changes value of data passed in to reflect what has
 left the queue.
*/
template <class T>
bool QfromStacks<T>::dequeue(T& data)
{
    shiftElements();
    return _oldest->pop(data);
}

#endif // Q_FROM_STACKS_H
