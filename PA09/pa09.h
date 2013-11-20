#ifndef PA09_H
#define PA09_H
#include <stdio.h>
#include <stdlib.h>

typedef struct _huffnode {
  int value; 
  struct _huffnode * left;
  struct _huffnode * right;
} HuffNode;

typedef struct _stack {
  struct _stack * next;
  HuffNode * node;
} Stack;

typedef struct _bit {
  FILE * fp;
  unsigned char byte;
} Bitfile;

Stack * stack_push(Stack *,HuffNode *);
Stack * stack_pop(Stack *);
HuffNode * huff_char(FILE *);
HuffNode * huff_bin(FILE *);
HuffNode * create(int);
void SparseArray_destroy(HuffNode *);
void Huff_postOrderPrint(HuffNode *,FILE *);
#endif

