#include <stdio.h>
#include <stdlib.h>
#include "pa09.h"

HuffNode * huff_char(FILE * fptr)
{
  int val;
  Stack * st = NULL;
  int command;
  if(fptr == NULL)
    {
      return NULL;
    }
  while(fptr != NULL)
    {
      command = fgetc(fptr);
      if(command == '1')
	{
	  val = fgetc(fptr);
	  HuffNode * tree = create(val);
	  st = stack_push(st,tree);
	}
      else
	{
	  HuffNode * A = st -> node;
	  st = stack_pop(st);
	  if(st == NULL)
	    {
	      return A;
	    }
	  else
	    {
	      HuffNode * B = st -> node;
	      st = stack_pop(st);
	      HuffNode * par = malloc(sizeof(HuffNode));
	      par -> value = ' ';
	      par -> right = A;
	      par -> left = B;
	      st = stack_push(st,par);
	    }
	}
    }
  return NULL;
}

HuffNode * huff_bin(FILE * fptr)
{
  unsigned char ch;
  unsigned char buff;
  int cmdloc = 1;
  int ct = 0;
  unsigned char buff_temp;
  unsigned char val;
  Stack * st = NULL;
  const unsigned char mask [] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
  unsigned char command = 0;
  ch = fgetc(fptr);
  while(1)
    {
      command = (ch & mask[ct]);
      if(command != 0)
	{
	  buff = fgetc(fptr);
	  val = ch << cmdloc;
	  buff_temp = buff >> (8 - cmdloc);
	  val = val | buff_temp;
	  HuffNode * tree = create(val);
	  st = stack_push(st,tree);
	  ch = buff;
	}
      else
	{
	  HuffNode * A = st -> node;
	  st = stack_pop(st);
	  if(st == NULL)
	    {
	      return A;
	    }
	  else
	    {
	      HuffNode * B = st -> node;
	      st = stack_pop(st);
	      HuffNode * par = malloc(sizeof(HuffNode));
	      par -> value = ' ';
	      par -> right = A;
	      par -> left = B;
	      st = stack_push(st,par);	      
	     
	    }  
	}
      	
      if(cmdloc == 8)
	{
	  ch = fgetc(fptr);
	  ct = 0;
	  cmdloc = 1;
	}
      else
	{
	  cmdloc++;
	  ct++;
	}
    }
  return NULL;
}

HuffNode * create(int val)
{
  HuffNode * tree = malloc(sizeof(HuffNode));
  tree -> value = val;
  tree -> left = NULL;
  tree -> right = NULL;
  return tree;
}

Stack * stack_pop(Stack * head)
{
  if(head == NULL)
    {
      return NULL;
    }
  Stack * temp = head -> next;
  free(head);
  return temp;
}

Stack * stack_push(Stack * st,HuffNode * t)
{
  Stack * topnode = malloc(sizeof(Stack));
  topnode -> node = t;
  topnode -> next = st;
  return topnode;
}

void SparseArray_destroy (HuffNode * array)
{
  if(array == NULL)
    {
      return;
    }
  SparseArray_destroy(array -> left);
  SparseArray_destroy(array -> right);
  free(array);
}

void Huff_postOrderPrint(HuffNode *tree,FILE * fptr)
{
    // Base case: empty subtree
    if (tree == NULL) 
      {
	return;
      }
    // Recursive case: post-order traversal
    // Visit left
    fprintf(fptr,"Left\n");
    Huff_postOrderPrint(tree->left,fptr);
    fprintf(fptr,"Back\n");
    // Visit right
    fprintf(fptr,"Right\n");
    Huff_postOrderPrint(tree->right,fptr);
    fprintf(fptr,"Back\n");
    // Visit node itself (only if leaf)
    if (tree->left == NULL && tree->right == NULL) 
      {
	fprintf(fptr,"Leaf: %c\n", tree->value);
      }
}



