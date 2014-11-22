/**
 Main function to test the linked (dynamic) implementations of several template data structures.
    This includes: dynamic queue implemented using pointers
                   dynamic stack implemented using pointers
                   dynamic imitation of how a queue operates using 2 stacks based on LIFO/ FIFO concept
*/

#include <iostream>
#include "singlyNode.h"
#include "LinkedStack.h"
#include "LinkedQueue.h"
#include "QfromStacks.h"


using namespace std;


void testStack();
void testQueue();
void testQfromStacks();
void testNodeWMin();

int main()
{
/** Uncomment functions below to test each data structure.
*/
    //testStack();
    //testQueue();
    testQfromStacks();
    return 0;
}

void testStack()
{
    cout << "\nTesting the Dynamic Stack" << endl;
    LinkedStack<int>* myStack = new LinkedStack<int>;
    for(int i = 0; i<5; i++)
        myStack->push(i);

    cout<<"Top element: "<<myStack->getTop()<<endl;

    for(int i = 0; i<5; i++)
    {
        myStack->pop();
    }
    delete myStack;
}
void testQueue()
{
    cout << "\nTesting the Dynamic Queue" << endl;
    LinkedQueue<int>* myQueue = new LinkedQueue<int>;

    for(int i = 0; i<5; i++)
        myQueue->enqueue(i);

    cout<<"Front element: "<<myQueue->getFront()<<endl;

    for(int i = 0; i<5; i++)
        myQueue->dequeue();

    delete myQueue;
}

void testQfromStacks()
{
    cout << "\nTesting the Dynamic Queue Made from 2 Stacks" << endl;
    QfromStacks<int>* TwoStacks = new QfromStacks<int>;
    for(int i = 0; i<5; i++)
        TwoStacks->enqueue(i);

    cout<<"Imitated queue has: "<<TwoStacks->getCount()<<" elements."<<endl;

    cout<<"Front element: "<<TwoStacks->getFront()<<endl;

    for(int i = 0; i<5; i++)
        TwoStacks->dequeue();

    cout<<"Imitated queue has: "<<TwoStacks->getCount()<<" elements."<<endl;

    delete TwoStacks;
}
