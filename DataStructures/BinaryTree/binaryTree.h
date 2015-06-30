// Specification file for the BinaryTree class
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

using namespace std;

struct Data
{
   int num;
   // more fields could be added if needed
};

class BinaryTree
{
private:
   struct BT_Node
   {
      Data data;        // The value in this node
      BT_Node *left;    // To point to the left node
      BT_Node *right;   // To point to the right node
   };

   BT_Node* root;       // root of the tree
   int count;           // number of nodes in the tree

public:
   // Constructor
   BinaryTree();

   // Destructor
   ~BinaryTree();

   // Binary Tree operations
   void BT_insert(Data dataIn);
   void BT_InorderTraverse() const;

private:
    void _BT_InorderTraverse( BT_Node *root ) const;
    void _BT_Destroy(BT_Node *root);
};
#endif
