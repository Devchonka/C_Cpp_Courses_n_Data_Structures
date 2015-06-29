#include "LinkedList.h"
using namespace std;

singlyNode* singlyNode:: getNext()
{
    return _next;
}

int singlyNode:: getData()
{
    return _data;
}

void singlyNode:: setNext(singlyNode* pNew)
{
    _next = pNew;
}

singlyLinkedList:: ~singlyLinkedList()
{
    destroyList();
}

int singlyLinkedList:: getCount()
{
    return _count;
}

void singlyLinkedList:: insertNode(int data)
{
    singlyNode* pWalk = _sentinel;
    singlyNode* pNewNode = new singlyNode(data);
    if(!pNewNode)
    {
        cout << "Error: Memory allocation error in insert. "<<endl;
        exit(1);
    }
    while(pWalk->getNext()) // make pWalk point to last element in list
    {
        pWalk = pWalk->getNext();
    }
    pWalk->setNext(pNewNode);
    _count++;
}

void singlyLinkedList:: circularizeTo(int elementNumber)
{
    if(_count <= elementNumber)
    {
        cout << "Error: Less elements than circularize to."<<endl;
        exit(1);
    }
    singlyNode* pWalk= _sentinel;
    for(int i = 0; i < elementNumber; i++)
    {
        pWalk = pWalk->getNext();
    }
    singlyNode* pEnd = pWalk;
    while(pEnd->getNext())
    {
        pEnd = pEnd->getNext();
    }
    pEnd->setNext(pWalk);
    cout<< "Added a loop from last element to element #" << elementNumber<<endl;
}

void singlyLinkedList:: printList()
{
    singlyNode *pWalk = _sentinel;
    while(pWalk->getNext())
    {
        cout<< pWalk->getData() <<endl;
        pWalk = pWalk->getNext();
    }
}

void singlyLinkedList:: destroyList()
{
    singlyNode *pPrev, *pWalk = _sentinel;
    while(pWalk->getNext())
    {
        pWalk = pWalk->getNext();
        delete pPrev;
        pPrev = pWalk;
    }
    delete pWalk;
}

bool singlyLinkedList:: containsCycle()
{
    singlyNode *pSlow, *pFast = _sentinel;
    while(pSlow && pFast && pFast->getNext())
    {
        pSlow = pSlow->getNext();
        pFast = pFast->getNext()->getNext();

        if (pFast == pSlow) // loop found
                return true;
    }
    return false;
}
