/**
    File BST.c is the source for the BST.h header. It holds definitions for the binary search tree functions.
*/

#include "BST.h"
#include "queue.h"

/****************************************************************
   INORDER
   Print a BST in Left-Root-Right sequence.
*/
void printTreeInorder(bstNODE* root, FILE* ofp)
{
    if(root)
    {
        printTreeInorder(root->left, ofp);
        fprintf(ofp, "\n %d %s",  root->bstData.freq, root->bstData.word);
        qNODE* front = dequeue(&(root)->bstData.q_front, &(root)->bstData.q_rear);
        while(front)
        {
            fprintf(ofp, " %d.%d", front->data.page, front->data.line);
            free(front);
            front = dequeue(&(root)->bstData.q_front, &(root)->bstData.q_rear);
        }
        printTreeInorder(root->right, ofp);
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
void insert_bstNode(bstNODE** root, char* new_word, int line_num, FILE_INFO* fileInf)
{
    bstNODE** ptr_root = root;
    while(*ptr_root)
    {
        if(strcmp(new_word,(*ptr_root)->bstData.word)>0) // go right in tree
        {
            ptr_root = &(*ptr_root)->right;
        }
        else if(strcmp(new_word,(*ptr_root)->bstData.word)<0) // go left in tree
        {
            ptr_root = &(*ptr_root)->left;
        }
        else // node already exists in the tree : no duplicate lines!
        {
            free(new_word);
            new_word = NULL;
            int temp_lineNum = peek_lineNum((*ptr_root)->bstData.q_rear);
            (*ptr_root)->bstData.freq++;
            if(temp_lineNum != line_num)
            {
                qDATA qdata = {fileInf->num_pages, line_num};
                enqueue(&(*ptr_root)->bstData.q_front, &(*ptr_root)->bstData.q_rear, qdata);
            }
            break;
        }
    }
    if(new_word) // node is not already existing in tree.. add it as a new token
    {
        if(!(*ptr_root = (bstNODE *) malloc(sizeof(bstNODE))))
        {
            printf("Error: Fatal malloc error!\n");
            exit(1);
        }
        bstDATA newTreeData = {new_word, 1, NULL, NULL};
        qDATA qdata = {fileInf->num_pages, line_num};
        enqueue(&newTreeData.q_front, &newTreeData.q_rear, qdata);
        fileInf->num_distinct_words++;
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
        freeTree(root->right);
        free(root->bstData.word);
        //Queue has already been freed during traversal
        free(root);
        root = NULL;
    }
    return root;
}
