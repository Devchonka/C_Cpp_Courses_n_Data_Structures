#include <iostream>

#include "LinkedList.h"
void LL_cycles();

using namespace std;

int main()
{
    LL_cycles();
    return 0;
}


void LL_cycles()
{
    // create singly linked list and populate with 10 numbers, make a loop to 3rd
    singlyLinkedList List;

    for(int i=0; i<10; i++)
    {
        int num = rand()%100+1;
        List.insertNode(num);
    }
    cout<<"hello!"<<endl;
    List.printList();
    List.circularizeTo(3);
    //List.printList();
    cout << List.containsCycle()<<endl; // test list if contains cycle
    cout<<"DONE WITH LIST!"<<endl;
    //List.printList();
}
