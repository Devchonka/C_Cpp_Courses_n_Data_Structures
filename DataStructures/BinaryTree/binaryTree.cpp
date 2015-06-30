// Implementation file for the BinaryTree class
#include <iostream>  // For cout and NULL


#include "binaryTree.h"
#include <cstdlib>   // For rand()
#include <ctime>     // For srand()
using namespace std;

/**~*~*
   Constructor
*~**/
BinaryTree::BinaryTree()
{
    root = NULL;
    count = 0;
}

/**~*~*
   This function calls a recursive function to traverse the
   tree in inorder
*~**/
void BinaryTree::BT_InorderTraverse() const
{
    _BT_InorderTraverse(root);
}

/**~*~*
   Inorder Traversal of the Binary Tree:
   Left-Root-Right
*~**/
void BinaryTree::_BT_InorderTraverse(BT_Node *root) const
{
    if (root)
    {
        _BT_InorderTraverse(root->left);
        cout << root->data.num << endl;
        _BT_InorderTraverse(root->right);
    }
}

/**~*~*
   Insert data into a random Binary Tree
*~**/
void BinaryTree::BT_insert(Data dataIn)
{
    BT_Node *newNode;
    BT_Node *pWalk;
    BT_Node *parent;
    int  rand_num;

    // allocate the new node
    newNode = new BT_Node;
    newNode->data  = dataIn;
    newNode->left  = NULL;
    newNode->right = NULL;

    // find a "random" parent
    if (!root) // tree is empty
        root = newNode;
    else
    {
        pWalk = root;
        while( pWalk ){
            parent   = pWalk;
            rand_num = rand( ) % 100;
            if( rand_num % 2 ) // if odd - take left
                pWalk = pWalk->left;
            else
                pWalk = pWalk->right;
        }

        // insert the new node
        if( !parent->left ) // no left child
             parent->left  = newNode;
        else
             parent->right = newNode;
    }

    count++;
}


/**~*~*
   Destructor
   This function calls a recursive function to delete all nodes in the binary tree
*~**/
BinaryTree::~BinaryTree()
{
    if (root)
        _BT_Destroy(root);
}

/**~*~*
   This function traverses the binary tree in postorder and deletes every node
*~**/
void BinaryTree::_BT_Destroy(BT_Node *root)
{
    if (root)
    {
        _BT_Destroy(root->left);
        _BT_Destroy(root->right);
        delete root;
    }
    return;
}




