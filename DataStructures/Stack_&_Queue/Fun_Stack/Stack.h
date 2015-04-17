/**~*~*
   Stack template
*~**/
#ifndef DYNAMICSTACK_H
#define DYNAMICSTACK_H
#include <iostream>
using namespace std;

template <class T>
class Stack
{
private:
    // Structure for the stack nodes
    struct StackNode
    {
        T value;          // Value in the node
        StackNode *next;  // Pointer to next node
    };

    StackNode* top;     // Pointer to the stack top
    int count;

public:
    //Constructor
    Stack()
    {
        top = NULL;
        count = 0;
    }

    // Destructor
    ~Stack();

    // Stack operations
    bool push(T);
    bool pop(T &);
    bool isEmpty() const;
    int getCount() const;
    T getTop() const;
};
/**~*~*
   Destructor
*~**/
template <class T>
Stack<T>::~Stack()
{
    StackNode *currNode, *nextNode;

    // Position nodePtr at the top of the stack.
    currNode = top;

    // Traverse the list deleting each node.
    while (currNode) //while (currNode != NULL)
    {
        nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }
}
/**~*~*
  Member function push pushes the argument onto
  the stack.
*~**/
template <class T>
bool Stack<T>::push(T item)
{
    StackNode *newNode; // Pointer to a new node

    // Allocate a new node and store num there.
    newNode = new StackNode;
    if (!newNode)
        return false;
    newNode->value = item;

    // Update links and counter
    newNode->next = top;
    top = newNode;
    count++;

    return true;
}
/**~*~*
  Member function pop pops the value at the top
  of the stack off, and copies it into the variable
  passed as an argument.
*~**/
template <class T>
bool Stack<T>::pop(T &item)
{
    StackNode *temp; // Temporary pointer

    // empty stack
    if (count == 0)
        return false;

    // pop value off top of stack
    item = top->value;
    temp = top->next;
    delete top;
    top = temp;
    count--;
    return true;
}
/**~*~*
  Member function isEmpty returns true if the stack
  is empty, or false otherwise.
*~**/
template <class T>
bool Stack<T>::isEmpty() const
{
    return count == 0;
}
/**~*~*
  Member function getCount returns number of items in stack.
*~**/
template <class T>
int Stack<T>:: getCount() const
{
    return count;
}
/**~*~*
  Member function getTop returns top item on stack without changing stack.
*~**/
template <class T>
T Stack<T>:: getTop() const
{
    return top->value;
}
#endif
