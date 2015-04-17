/**
 Linked (dynamic) implementation of a queue.
*/

#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include "singlyNode.h"

template<class T>
class LinkedQueue
{
private:
    int _count;
    singlyNode<T>* _front;
    singlyNode<T>* _rear;

public:
    LinkedQueue(): _count(0), _front(nullptr), _rear(nullptr) {};
    ~LinkedQueue();
    bool isEmpty() const;
    int getCount() const;
    T getFront() const;
    bool enqueue(const T);
    bool dequeue();
    bool dequeue(T&);
};

/**
 Destructor deletes all nodes from queue, which is all that was dynamically allocated.
*/
template<class T>
LinkedQueue<T>::~LinkedQueue()
{
    singlyNode<T>* currPtr = _front;
    while (currPtr)
    {
        currPtr=currPtr->getNodeF();
        delete _front;
        _front = currPtr;
    }
}

/**
 Enqueue adds data passed as parameter into the rear of the queue, and increments the count.
*/
template<class T>
bool LinkedQueue<T>::enqueue(const T data)
{
    singlyNode<T>* newNode = new singlyNode<T>(data);
    bool ableToEnqueue = (newNode);
    newNode->setNodeF(nullptr);
    if (ableToEnqueue)
    {
        if (_front==nullptr)
            _front = newNode;
        else
            _rear->setNodeF(newNode);

        _rear = newNode;
        _count++;
        std::cout<<"Enqueued "<<newNode->getNodeData()<<" into queue"<<std::endl;
    }
    return ableToEnqueue;
}

/**
 Dequeue removes data from front of queue, and decrements the count. This version does not return what is dequeued.
*/
template<class T>
bool LinkedQueue<T>::dequeue()
{
    bool ableToDequeue = !isEmpty();
    if (ableToDequeue)
    {
        singlyNode<T>* currPtr =_front->getNodeF();
        std::cout<<"Dequeued "<<_front->getNodeData()<<" from queue"<<std::endl;
        delete _front;
        _count--;
        _front = currPtr;
    }
    return ableToDequeue;
}

/**
 Dequeue removes data from front of queue, and decrements the count. This version does not return what is dequeued
 through the parameter reference data.
*/
template<class T>
bool LinkedQueue<T>::dequeue(T& data)
{
    bool ableToDequeue = !isEmpty();
    if (ableToDequeue)
    {
        singlyNode<T>* currPtr =_front->getNodeF();
        data = _front->getNodeData();
        delete _front;
        _count--;
        _front = currPtr;
        std::cout<<"Dequeued "<<data<<" from queue"<<std::endl;
    }
    return ableToDequeue;
}

/**
 Returns true is queue is empty, false otherwise.
*/
template<class T>
bool LinkedQueue<T>::isEmpty() const
{
    return _count==0;
}

/**
 Returns the number of elements currently in the queue.
*/
template<class T>
int LinkedQueue<T>::getCount() const
{
    return _count;
}

/**
 Returns a copy of the element at the front of the queue.
*/
template<class T>
T LinkedQueue<T>::getFront() const
{
    if (_front == nullptr)
    {
        std::cerr << "Attempt to peek at an empty queue!" << std::endl;
        exit(1);
    }
    return _front->getNodeData();
}

#endif // LINKED_QUEUE_H
