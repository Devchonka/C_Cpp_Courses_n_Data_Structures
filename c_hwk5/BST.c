/**
    File BST.c is the source for the BST.h header. It holds definitions for the binary search tree functions.
*/

#include "BST.h"
#include "queue.h"

/****************************************************************
   INORDER
   Print a BST in Left-Root-Right sequence.
*/
void printTreeInorder(bstNODE* root)
{
    if(root)
    {
        printTreeInorder(root->left);
        printf("\n %d %s",  root->bstData.freq, root->bstData.word);
        qNODE* front = dequeue(&(root)->bstData.q_front, &(root)->bstData.q_rear);
        while(front)
        {
            //printf(" %d.%d", root->bstData.q_front->data.page, root->bstData.q_front->data.line);
            front = dequeue(&(root)->bstData.q_front, &(root)->bstData.q_rear);
        }
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
void insert_bstNode(bstNODE** root, char* new_word, int line_num, int page_num)
{
    bstNODE** ptr_root = root;
    while(*ptr_root)
    {
        if(strcmp(new_word,(*ptr_root)->bstData.word)>0)
        {
            ptr_root = &(*ptr_root)->right;
        }
        else if(strcmp(new_word,(*ptr_root)->bstData.word)<0)
        {
            ptr_root = &(*ptr_root)->left;
        }
        else
        {
            free(new_word);
            new_word = NULL;
            (*ptr_root)->bstData.freq++;
            qDATA qdata = {page_num, line_num};
            enqueue(&(*ptr_root)->bstData.q_front, &(*ptr_root)->bstData.q_rear, qdata);
            break;
        }
    }
    if(new_word)
    {
        if(!(*ptr_root = (bstNODE *) malloc(sizeof(bstNODE))))
        {
            printf("Error: Fatal malloc error!\n");
            exit(1);
        }
        bstDATA newTreeData = {new_word,0, NULL, NULL};
        newTreeData.freq++;
        qDATA qdata = {page_num, line_num};
        enqueue(&(*ptr_root)->bstData.q_front, &(*ptr_root)->bstData.q_rear, qdata);
        (*ptr_root)->bstData  = newTreeData;
        (*ptr_root)->left  = (*ptr_root)->right = NULL;
    }
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

/**
    Function freeTree frees all the dynamically allocated memory to avoid memory leaks.
*/
void* freeTree(bstNODE* root)
{
    if(root)
    {
        freeTree(root->left);
        free(root->bstData.word);
        free(root);
        freeTree(root->right);
    }
    return NULL;
}
