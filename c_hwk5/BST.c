#include "BST.h"

/****************************************************************
   INORDER
   Print a BST in Left-Root-Right sequence.
*/
void printTreeInorder(bstNODE *root)
{
    if(root)
    {
        printTreeInorder(root->left);
        printf("%s\n",  root->bstData.word);
        printTreeInorder(root->right);
    }
    return;
}

/****************************************************************
   Build a BST

bstNODE* buildBinaryTree()
{
    bstNODE* root = NULL;
    bstDATA newTreeData;
    newTreeData.word = "hi";

    while(n)
    {
        if(insert(&root, newTreeData)) // not a duplicate!
        {
            n--;
        }
    }
    return root;
}
*/
/****************************************************************
   ITERATIVE Insert
*/
int insert(bstNODE **root, bstDATA newBstData)
{
    bstNODE **ptr_root = root;
    while(*ptr_root)
    {
        if(strcmp(newBstData.word,(*ptr_root)->bstData.word)>0) //bstData.word > (*ptr_root)->word
        {
            ptr_root = &(*ptr_root)->right;
        }
        else if(strcmp(newBstData.word,(*ptr_root)->bstData.word)<0)
        {
            ptr_root = &(*ptr_root)->left;
        }
        else // Node already in the tree
        {
            //printf("increment freq in word %s\n", newBstData.word);
            break;
            return 0; // duplicate
        }
    }
    if(!(*ptr_root = (bstNODE *) malloc(sizeof(bstNODE))))
    {
        printf("Fatal malloc error!\n"), exit(1);
    }
    (*ptr_root)->bstData  = newBstData;
    (*ptr_root)->left  = (*ptr_root)->right = NULL;
    return 1; // data inserted
}

/****************************************************************
   RECURSIVE Insert

int insert( NODE **root, int data )
{

   if(!(*root)){ // parent found: insert data
      // allocate the new node
      if(!(*root = (NODE *) malloc (sizeof(NODE))))
         printf( "Fatal malloc error!\n" ), exit(1);
      (*root)->data  = data;
      (*root)->left  = (*root)->right = NULL;
      return 1; // data inserted
   }

   if (data > (*root)->data)
      return insert(&(*root)->right, data);
   else if (data < (*root)->data)
      return insert(&(*root)->left, data);
   else
   {
       printf("Node already in the tree!\n");
       return 0; // duplicate
   }
}
*/
/****************************************************************
   ITERATIVE Search
*/
bstNODE *find(bstNODE* root, char* target)
{
    bstNODE* mover = root;
    while(mover)
    {
        if(strcmp(target, mover->bstData.word)< 0)
        {
            mover = mover->left;
        }
        else if(strcmp(target, mover->bstData.word)>0)
        {
            mover = mover->right;
        }
        else
        {
            return mover;
        }
    }
    return NULL;
}

/****************************************************************
   RECURSIVE Search

NODE *find(NODE *root, int target)
{
   if (root)
   {
       if (target < root->data)
           return find(root->left, target);
       else
           if (target > root->data)
               return find(root->right, target);
           else
               return root;
   }
   return NULL;
}
*/
