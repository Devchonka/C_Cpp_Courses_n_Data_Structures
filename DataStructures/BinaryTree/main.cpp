/**
 Project: BUILD A RANDOM BINARY TREE

 The main goal of this example is build a binary tree that could be used to
 test the traversal functions and other binary tree functions

 NAME:
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdlib>
#include <ctime>
#include "binaryTree.h"

using namespace std;

void build_BT( BinaryTree &tree, int n );

int main( void )
{
   BinaryTree tree;
   int n = 6; // number of nodes

   build_BT(tree, n );
   tree.BT_InorderTraverse();
   cout << endl << endl;

   return 0;
}

/**~*~*
   Builds a random Binary Tree of integer numbers within the range
   [0, 99]; root is always 50
*/
void build_BT( BinaryTree &tree, int n )
{
    Data data = {50};

    // allocate and initialize the root
    tree.BT_insert(data);

    srand(time(NULL));
    while(--n)
    {
        data.num = rand( ) % 100;
        tree.BT_insert(data);
   }
}
