/**
    This file include singly linked list definitions.
*/

#include <iostream>

class singlyNode
{
    int _data;
    singlyNode* _next;

public:
    singlyNode(int data): _data(data), _next(nullptr) {};
    singlyNode* getNext();
    int getData();
    void setNext(singlyNode*);
};


class singlyLinkedList
{
    int _count;
    singlyNode* _sentinel;

public:
    singlyLinkedList(): _count(0), _sentinel(new singlyNode(0)) {};
    ~singlyLinkedList();
    int getCount();
    void insertNode(int);
    void circularizeTo(int);
    void printList();
    void destroyList();

    //cycle functions
    bool containsCycle();
};


