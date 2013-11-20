#include "pa08.h"
#include <stdio.h>
#include <stdlib.h>

/* 
 * Create a single instance of a sparse array tree node with a specific
 * index and value. This Sparse array will be implemented by a binary tree.
 *
 * Arguments:
 * index         the index to be stored in the node
 * value         the value to be stored in the node
 * 
 * returns:
 * SparseNode *  the pointer points to the node just constructed
 *
 * This is a constructor function that allocates
 * memory for a sparse array tree node, and it copies the integer values, and sets the 
 * subtree pointers to NULL. 
 */

SparseNode *SparseNode_create(int index, int value)
{
  SparseNode *node = malloc(sizeof(SparseNode));
  node -> index = index;
  node -> value = value;
  node -> left = NULL;
  node -> right = NULL;
  return node;
}

/* Add a particular value into a sparse array tree on a particular index.
 *
 * Arguments:
 * *array        the root node of the sparse array tree
 * index         the index to be stored in the node
 * value         the value to be stored in the node
 * 
 * returns:
 * SparseNode *  the pointer points to the root node of the modified sparse 
 *               array tree
 *
 * The sparse array tree uses the index as a key in a binary search tree.
 * If the index does not exist, create it. 
 * If the index exists, REPLACE the value to the new one. Use the index to
 * determine whether to go left or right in the tree (smaller index
 * values than the current one go left, larger ones go right).
 */

SparseNode * SparseArray_insert ( SparseNode * array, int index, int value )
{
  if(array == NULL)
    {
      return SparseNode_create(index,value);
    }
  if(array -> index == index)
    {
      array -> value = value;
      return array;
    }
  if(index < array -> index)
    {
      array -> left = SparseArray_insert(array -> left,index,value);
      return array;
    }
  if(index > array -> index)
    {
      array -> right = SparseArray_insert(array -> right,index,value);
    }
  return array;
}

/* Build a sparse array tree from given indices and values with specific length.
 *
 * Arguments:
 * index*         a pointer points to the start position of the index array
 * value*         a pointer points to the start position of the value array
 * length         the size of both array
 * 
 * returns:
 * SparseNode *   the pointer points to the root node of sparse array tree
 *                just constructed
 *
 * It returns a sparse array tree. 
 * You need to insert tree nodes in order
 *
 * (the first sparse array node contains indices[0] and values[0], second node
 * contains indices[1] and values[1]. Basically, each tree node is constructed
 * with each pair in indices and values array. In other words, elements of 
 * indices and values with the same index should go into the same node.)
 */

SparseNode *SparseArray_build(int * indicies, int * values, int length)
{
  SparseNode *node = NULL;
  int ct;
  for(ct = 0;ct < length;ct++)
    {
      if(values[ct] == 0)
	{
	}
      else
	{
	  node = SparseArray_insert(node,indicies[ct],values[ct]);
	}
    }
  return node;
}

/* Destroy an entire sparse array tree. 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * void
 *
 * traversing the binary tree in postorder. Use the
 * SparseNode_destroy () function to destroy each node by itself.
 */
void SparseArray_destroy ( SparseNode * array )
{
  if(array == NULL)
    {
      return;
    }
  SparseArray_destroy(array -> left);
  SparseArray_destroy(array -> right);
  free(array);
}

/* Retrieve the smallest index in the sparse array tree.
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * int            the smallest index in the sparse array tree
 *
 * (Hint: consider the property of binary search tree) 
 */
int SparseArray_getMin ( SparseNode * array )
{
  while(array -> left != NULL)
    {
      array = array -> left;
    }
  return (array -> index);
}

/* Retrieve the largest index in the sparse array tree. 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * int            the largest index in the sparse array tree
 *
 * (Hint: consider the property of binary search tree) 
 */
int SparseArray_getMax ( SparseNode * array )
{
  while(array -> right != NULL)
    {
      array = array -> right;
    }
  return (array -> index);
}


/* Retrieve the node associated with a specific index in a sparse
 * array tree.  
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * index          the index of the node you want to search
 * 
 * returns:
 * SparseNode*    the node with the index that you searched from the tree.
 *                If no node found, NULL should be returned. 
 *                
 * Hint: If the given index is smaller than the current
 * node, search left ; if it is larger, search right.
 */
SparseNode * SparseArray_getNode(SparseNode * array, int index )
{
  if(array == NULL)
    {
      return NULL;
    }
  if(index == array -> index)
    {
      return array;
    }
  if(index > array -> index)
    {
      return SparseArray_getNode(array -> right,index);
    }
  if(index < array -> index)
    {
      return SparseArray_getNode(array -> left,index);
    }
  return array;
}

/* Remove a value associated with a particular index from the sparse
 * array. It returns the new
 * sparse array tree ( binary tree root ). 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * index          the index of the node you want to remove
 * 
 * returns:
 * SparseNode*    the root node of the sparse array tree that you just modified
 *          
 *    
 * HINT : First, you need to find that node. Then, you will need to isolate
 * several different cases here :
 * - If the array is empty ( NULL ), return NULL
 * - Go left or right if the current node index is different.

 * - If both subtrees are empty, you can just remove the node.

 * - If one subtree is empty, you can just remove the current and
 * replace it with the non - empty child.

 * - If both children exist, you must find the immediate successor of
 * the current node ( leftmost of right branch ), swap its values with
 * the current node ( BOTH index and value ), and then delete the
 * index in the right subtree.
*/
SparseNode * SparseArray_remove ( SparseNode * array, int index )
{
  if(array == NULL)
    {
      return NULL;
    }
  if(index < array -> index)
    {
      array -> left = SparseArray_remove(array -> left,index);
      return array;
    }
  if(index > array -> index)
    {
      array -> right = SparseArray_remove(array -> right,index);
      return array;
    }
  if((array -> right == NULL) && (array -> left == NULL))
    {
      free(array);
      return NULL;
    }
  if(array -> right == NULL)
    {
      SparseNode * cp = array -> left;
      free(array);
      return cp;
    }
  if(array -> left == NULL)
    {
      SparseNode * cp2 = array -> right;
      free(array);
      return cp2;
    } 
  SparseNode * cp3 = array -> right;
  while(cp3 -> left != NULL)
    {
      cp3 = cp3 -> left;
    }
  array -> index = cp3 -> index;
  array -> value = cp3 -> value;
  cp3 -> index = index;
  array -> right = SparseArray_remove(array -> right,index);
  return array;
}

/* The function makes a copy of the input sparse array tree
 * and it returns a new copy. 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * SparseNode*    the root node of the new sparse array tree that you just
 *                copied from the input sparse array tree.
 *       
 */
SparseNode * copy_helper(SparseNode *,SparseNode *);

SparseNode * SparseArray_copy(SparseNode * array)
{
  if(array == NULL)
    {
      return NULL;
    }
  SparseNode * cp = SparseNode_create(array -> index,array -> value); 
  cp = copy_helper(cp,array);
  return cp;
}

SparseNode * copy_helper(SparseNode * cp,SparseNode * array)
{
  if(array == NULL)
    {
      return NULL;
    }
  cp = SparseArray_insert(cp,array -> index,array -> value);
  cp -> left = copy_helper(cp -> left,array -> left);
  cp -> right = copy_helper(cp -> right,array -> right);
  return cp;
}

/* Merge array_1 and array_2, and return the result array. 
 * This function WILL NOT CHANGE the contents in array_1 and array_2.
 *
 * Arguments:
 * *array_1         the root node of the first sparse array tree
 * *array_2         the root node of the second sparse array tree
 * 
 * returns:
 * SparseNode*    the root node of the new sparse array tree that you just
 *                merged from the two input sparse array tree
 *     
 * When merging two sparse array tree:
 * 1. The contents in array_1 and array_2 should not be changed. You should make
 *    a copy of array_1, and do merging in this copy.
 * 2. array_2 will be merged to array_1. This means you need to read nodes in 
 *    array_2 and insert them into array_1.
 * 3. You need to use POST-ORDER to traverse the array_2 tree. 
 * 4. Values of two nodes need to be added only when the indices are the same.
 * 5. A node with value of 0 should be removed.
 * 6. if array_2 has nodes with index different than any nodes in array_1, you
 *    should insert those nodes into array_1.
 * 
 * Hint: you may write new functions
 */
SparseNode * merge_helper(SparseNode *,SparseNode *);
SparseNode * merge_insert(SparseNode *,int,int);

SparseNode * SparseArray_merge(SparseNode * array_1, SparseNode * array_2)
{
  SparseNode * cp = SparseArray_copy(array_1);
  cp = merge_helper(cp,array_2);
  return cp;
}

SparseNode * merge_helper(SparseNode * cp,SparseNode * array)
{  
  if(array == NULL)
    {
      return cp;
    }
  cp = merge_helper(cp,array -> left);
  cp = merge_helper(cp,array -> right);
  cp = merge_insert(cp,array -> index,array -> value);
  return cp;
}

SparseNode * merge_insert(SparseNode * cp,int index,int value)
{
  if(cp == NULL)
    {
      cp = SparseNode_create(index,value);
      return cp;
    }
  if(cp -> index == index)
    {
      cp -> value += value;
      if(cp -> value == 0)
	{
	  cp = SparseArray_remove(cp,index);
	}
      return cp;
    }
  if(cp -> index > index)
    {
      cp -> left = merge_insert(cp -> left,index,value);
    }
  else
    {
      cp -> right = merge_insert(cp -> right,index,value);
    }
  return cp;
}

/*void dump(SparseNode*);

void dump(SparseNode* node)
{
  if(node == NULL)
    {
      return;
    }
  printf("\n[%p] index = %d value = %d left = %p right = %p\n",node,node -> index,node -> value,node -> left, node -> right);
  dump(node -> left);
  dump(node -> right);
}


#ifdef MYTEST

// gcc -g -Wall -Wshadow -DMYTEST -o answer07 answer07.c && ./answer07
int main(int argc, char * * argv)
{
  int val[8] = {4,1,2,4,1,5,8,3};
  int ind[8] = {5,2,7,1,9,6,4,3};
  printf("\nAbout to run my custom test-cases\n");
  // Test sparsenode create
  printf("\nSparseNode Create\n");
  SparseNode * head = SparseNode_create(7, 5);
  dump(head);
  //Insert
  printf("\nInsert\n");
  head = SparseArray_insert(head,10,3);
  head = SparseArray_insert(head,4,3);
  head = SparseArray_insert(head,1,3);
  head = SparseArray_insert(head,10,5);
  head = SparseArray_insert(head,8,3);
  head = SparseArray_insert(head,12,3);
  head = SparseArray_insert(head,5,3);
  dump(head);
  //Destroy
  printf("\nDestroy\n");
  SparseArray_destroy(head);
  dump(head);
  //Build
  printf("\nBuild\n");
  SparseNode * node;
  node = SparseArray_build(ind,val,8);
  dump(node);
  //Merge
  printf("\nMerge\n");
  int val2[8] = {2,4,5,7,8,9,1,-3};
  int ind2[8] = {1,5,7,3,8,9,2,3};
  SparseNode * Node2 = SparseArray_build(ind2,val2,8);
  dump(Node2);
  printf("\n--\n");
  SparseNode * Node3 = SparseArray_merge(node,Node2);
  dump(Node3);
  //Max and Min
  printf("\nMax\n");
  int max = SparseArray_getMax(node);
  int min = SparseArray_getMin(node);
  printf("\nMax = %d Min = %d\n",max,min);
  //Get Node
  printf("\nGet Node\n");
  SparseNode * getNode = SparseArray_getNode(node,7);
  dump(getNode);
  //Remove
  printf("\nRemove\n");
  node = SparseArray_remove(node,2);
  dump(node);
  //Copy
  printf("\nCopy\n");
  SparseNode * copy = SparseArray_copy(node);
  dump(copy);
  return 0;
}

#endif


*/

