#include "pa07.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Prints a linked-list "head" into the output file "out"
 *
 * NOTE: we have given the code for this function
 */
void List_print(FILE * out, Node * head)
{
 while(head != NULL)
	{
	    fprintf(out, "%5d: %6d\n", head -> index, head -> value);
	    head = head -> next;
	}
    printf("\n");
}

void List_dump(Node * head)
{
  FILE * out = stdout;
  while(head != NULL)
    {
      fprintf(out, "[%p] %5d: %6d ==> %p\n", head, head -> index, head -> value, head -> next);
      head = head -> next;
    }
  printf("\n");
}


/**
 * Please fill in the code below
 */

/**
 * Destroys a linked list.
 * Arguments:
 * head    A pointer pointing to the first element of the linked list.
 *
 * Returns:
 * void
 *
 * Destroys (frees memory for) the whole linked list. 
 * You can either use recursion or a while loop.
 */
void List_destroy(Node * head)
{
  if(head == NULL)
    {
      return;
    }
  List_destroy(head -> next);
  free(head);
}

/**
 * Create and initialize a linked list. 
 *
 * Arguments:
 * value     The "value" of the new node
 * index     The "index" of the new node
 *
 * Returns:
 * Returns a newly constructed node. The node can be the head of a
 * linked list.
 * 
 * You should allocate memory in this function. 
 */
Node * List_create(int value, int index)
{
  Node * lnc = malloc(sizeof(Node));
  lnc -> value = value;
  lnc -> index = index;
  lnc -> next = NULL;
  return lnc;
}

/**
 * Build a sparse array from the given indices and values with 
 * specific length.
 *
 * Arguments:
 * value    Array of values
 * index    Array of indices
 * length   Length of the above arrays
 *
 * Returns:
 * A sparse array.
 *
 * If a sparse array node has { value = 1000, index = 2 }, then that means that
 * the index "2" caries the value "1000". This is meant to convey an array of 1000 
 * "2s", but instead of creating 1000 nodes in your linked list, you only create
 * 1 node, and that note conceptually has 1000 "copies" of it. Hence 
 * each node in a sparse array has a "value" in addition to its "index".
 *
 * Note that an index can never carry the value of "0", because this would not make
 * any sense; however, negative values are fine. A negative value may seem odd
 * at first blush; however, this is like substraction, and makes sense for certain
 * cases.
 *
 * You need to insert nodes in ascending order by index.
 * See the notes to "List_insert_ascend"
 */
Node * List_build(int * value, int * index, int length)
{
  int ct;
  Node * p = NULL;
  for(ct = 0;ct < length;ct++)
    {
      if(value[ct] == 0)
	{
	  continue;
	}
      p = List_insert_ascend(p,value[ct],index[ct]);
    }
  return p;
}


/**
 * Inserting "value" and "index" into the correct location in the 
 * sparse array "head"
 * 
 * Arguments: 
 * head      A pointer pointing to the first element of the linked list.
 * value     The "value" of the value
 * index     The "value" of the index
 *
 * Returns:
 * A sparse array
 *
 * This function inserts the node ["value", "index"] into the sparse
 * array "head", and ensures that the nodes remain in ascending order
 * by their "index".
 *
 * Before and after the call to this function, "head" must be in
 * ASCENDING order by the "index" of each node.
 */
Node * List_insert_ascend(Node * head, int value, int index)
{
  if(head == NULL)
    {
      return List_create(value,index);
    }
  if((head -> index) > index)
    {
      Node* p = List_create(value,index);
      p -> next = head;
      return p;
    } 
  if((head -> index) == index)
    {
      return head;
    } 
  head -> next = List_insert_ascend(head -> next,value,index);
  return head;
}


/**
 * This function deletes the node with the passed "index"
 * 
 * Arguments: 
 * head      A pointer pointing to the first element of the sparse array.
 * index     The index to be deleted
 *
 * Returns: 
 * A sparse array with the node removed (the one with index)
 */
Node * List_delete(Node * head, int index)
{
  if(head == NULL)
    {
      return head;
    }
  if(head -> index == index)
    {
      Node * p = head -> next;
      free(head);
      return p;
    }
  head -> next = List_delete(head -> next,index);
  return head;
}

/**
 * Copy a list
 *
 * Arguments:
 * head      A pointer pointing to the first element of the sparse array
 *
 * Returns:
 * A copy sparse array
 *
 * This function will copy the sparse array that is passed to it. The
 * copy will be made into new memory. 
 *
 * This is useful, for example, when we want to merge
 * two linked lists together. We can make a copy of one of the linked
 * lists, and then merge the second into the copy. In this way the
 * original copy of the list is not "mutated".
 */
Node * Copy(Node *,Node *);

Node * List_copy(Node * head)
{
  if(head == NULL)
    {
      return head;
    }
  Node * p = List_create(head -> value,head -> index);
  head = head -> next;
  p = Copy(p,head);
  return p;
}

Node * Copy(Node * p,Node * head)
{
  if(head == NULL)
    {
      return p;
    }
  p = List_insert_ascend(p,head -> value,head -> index);
  head = head -> next;
  p -> next = Copy(p -> next,head);
  return p;
}

/**
 * Merged two linked list together
 * 
 * Arguments:
 * head1      A pointer pointing to linked list 1
 * head2      A pointer pointing to linked list 2
 *
 * Returns:
 * A merged sparse array
 *
 * This function will merge two linked lists. Before merging, you 
 * should make a copy of "head1" so that you will still have the 
 * original array while modifying (merging) the second linked list. 
 *
 * Please refer to the README file for detailed instructions on how to
 * merge two lists.
 *
 * This function should not modify either "head1" or "head2". You only
 * need to make a clone of "head1".
 */
Node * insert(Node *,int,int);

Node * List_merge(Node * head1, Node * head2)
{
  Node * head3;
  head3 = List_copy(head1);
  while(head2 != NULL)
    {
      head3 = insert(head3,head2 -> value,head2 -> index);
      head2 = head2 -> next;
    }
  return head3;
}

Node * insert(Node * head3,int value,int index)
{
  if(head3 == NULL)
    {
      return(List_create(value,index));
    }
  if((head3 -> index) == index)
    {
      head3 -> value += value;
      if(head3 -> value == 0)
	{
	  head3 = List_delete(head3,index);
	}
      return head3;
    }
  if((head3 -> index) > index)
    {
      Node * p = List_create(value,index);
      p -> next = head3;
      return p;
    }
  head3 -> next = insert(head3 -> next,value,index);
  return head3;
}

/*#ifdef MYTEST

// gcc -g -Wall -Wshadow -DMYTEST -o answer07 answer07.c && ./answer07
int main(int argc, char * * argv)
{
  int val[8] = {0,1,2,4,1,5,8,3};
  int ind[8] = {1,4,7,2,9,2,4,3};
  printf("\nAbout to run my custom test-cases\n");

  // Test list-create works
  Node * head = List_create(200, 5);
  // Test list-insert-ascend
  printf("\nInsert Ascend\n");
  head = List_insert_ascend(head,-5,1);
  head = List_insert_ascend(head,5,1);  
  head = List_insert_ascend(head,-6,3);
  head = List_insert_ascend(head,3,4);
  List_dump(head);
  printf("Build\n");
  Node * build = List_build(val,ind,8);
  List_dump(build);
  printf("Merge\n");
  Node * head2 = List_create(112,8);
  head2 = List_insert_ascend(head2,5,1);
  head2 = List_insert_ascend(head2,5,7);  
  head2 = List_insert_ascend(head2,-6,4);
  head2 = List_insert_ascend(head2,3,5);
  List_dump(head2);
  Node * head3 = List_merge(head,head2);
  List_dump(head3);
  printf("Delete\n");
  head = List_delete(head,1);
  List_dump(head);
  printf("Copy\n");
  Node * copy;
  copy = List_copy(head);
  List_dump(copy);
  printf("Destroy\n");
  List_destroy(head);  
  List_dump(head);
  return 0;
}

#endif
*/
