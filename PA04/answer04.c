/*
 * Please fill the functions in this file.
 * You can add additional functions. 
 *
 * Hint: 
 * You can write additonal functions.
 * You can test your functions with your own input file.
 * See details in README or typing command ./pa04 in terminal after make.
 * See output format examples in any of the files in directory expected.
 * 
 * You may create additional arrays if needed.  The maximum size
 * needed is specified by MAXLENGTH in pa04.h.
 */

#include "pa04.h"
#include <stdio.h>
#include <stdlib.h>



/*
 * =================================================================
 * This function prints all partitions of a positive integer value
 * For example, if the value is 3:
 *
 * partitionAll 3
 * = 1 + 1 + 1
 * = 1 + 2
 * = 2 + 1
 * = 3
 */
void partition(int);
void work_all(int *,int,int);
void print_arr(int *,int);

void partitionAll(int value)
{
  printf("partitionAll %d\n", value);
  partition(value);
}

void partition(int i)
{
  int *buffer;
  buffer = malloc(sizeof(int)*i);
  work_all(buffer,0,i);
  free(buffer);
}

void work_all(int *arr,int pos, int i)
{
  if(i <= 0)
    {
      print_arr(arr,pos);
      return;
    }
  int ct;
  for(ct = 1;ct <= i;++ct)
    {
      arr[pos] = ct;
      work_all(arr,pos + 1, i - ct);
    }
}

void print_arr(int *arr,int lth)
{
  int ct;
  if(lth > 0)
    {
      printf("=");
      for(ct = 0;ct < lth;ct++)
	{
	  printf(" %d",arr[ct]);
	  if(ct + 1 != lth)
	    {
	      printf(" +");
	    }
	}
      printf("\n");
    }
}
/*
 * =================================================================
 * This function prints the partitions that use increasing values.
 *
 * For example, if value is 5
 * 2 + 3 and
 * 1 + 4 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 3 + 2 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */
void partition_inc(int);
void work_inc(int *,int,int);

void partitionIncreasing(int value)
{
  printf("partitionIncreasing %d\n", value);

  partition_inc(value);
}

void partition_inc(int i)
{
  int *buffer;
  buffer = malloc(sizeof(int) * i);
  work_inc(buffer,0,i);
  free(buffer);
}

void work_inc(int *arr,int pos, int i)
{
  if(i <= 0)
    {
      print_arr(arr,pos);
      return;
    }
  int ct;
  for(ct = 1;ct <= i;++ct)
    {
      if(pos == 0 || ct > arr[pos - 1])
	{
	  arr[pos] = ct;
	  work_inc(arr,pos + 1, i - ct);
	}
    }
}

/*
 * =================================================================
 * This function prints the partitions that use Decreasing values.
 *
 * For example, if value is 5
 * 3 + 2 and
 * 4 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */
void partition_dec(int*,int,int);

void partitionDecreasing(int value)
{
  int *buffer = malloc(sizeof(int) * value);
  printf("partitionDecreasing %d\n", value);
  partition_dec(buffer,0,value);
  free(buffer);
}

void partition_dec(int *arr,int pos,int i)
{
    if(i <= 0)
    {
      print_arr(arr,pos);
      return;
    }
  int ct;
  for(ct = 1;ct <= i;++ct)
    {
      if(pos == 0 || ct < arr[pos - 1])
	{
	  arr[pos] = ct;
	  partition_dec(arr,pos + 1, i - ct);
	}
    }
}

/*
 * =================================================================
 * This function prints odd number only partitions of a positive integer value
 * For example, if value is 5
 * 1 + 1 + 1 + 1 + 1 and
 * 1 + 3 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 1 + 2 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

void work_odd(int *,int,int);

void partitionOdd(int value)
{
  int *buffer = malloc(sizeof(int) * value);
  printf("partitionOdd %d\n", value);
  work_odd(buffer,0,value);
  free(buffer);
}

void work_odd(int *arr,int pos,int i)
{
    if(i <= 0)
    {
      print_arr(arr,pos);
      return;
    }
  int ct;
  for(ct = 1;ct <= i;++ct)
    {
      if(ct % 2 == 1)
	{
	  arr[pos] = ct;
	  work_odd(arr,pos + 1, i - ct);
	}
    }
}
/*
 * =================================================================
 * This function prints even number only partitions of a positive integer value
 * For example, if value is 8
 * 2 + 2 + 2 + 2and
 * 2 + 4 + 2 are valid partitions
 *
 * 8 is a valid partition
 *
 * 2 + 1 + 1 + 2 + 2and
 * 2 + 1 + 2 + 3and
 * 5 + 3 are invalid partitions.
 *
 * if the value is 5, there will be no result generated
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */
void work_even(int *,int,int);

void partitionEven(int value)
{
  int *buffer = malloc(sizeof(int) * value);
  printf("partitionEven %d\n", value);
  work_even(buffer,0,value);
  free(buffer);
}

void work_even(int *arr,int pos,int i)
{
  if(i <= 0)
    {
      print_arr(arr,pos);
      return;
    }
  int ct;
  for(ct = 1;ct <= i;++ct)
    {
      if((ct % 2 == 0))
	{
	  arr[pos] = ct;
	  work_even(arr,pos + 1, i - ct);
	}
    }
}

/*
 * =================================================================
 * This function prints alternate ood and even number partitions of a positive integer value. Each partition starts from and odd number, even number, ood number again, even number again...etc.
 *
 * For example, if value is 6
 * 1 + 2 + 1 + 2 and
 * 3 + 2 + 1 are valid partitions
 *
 * 6 is not a valid partition
 *
 * 2 + 1 + 1 + 2 and
 * 2 + 1 + 3and
 * 5 + 1 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */
void work_evenodd(int *,int,int);

void partitionOddAndEven(int value)
{
  int *buffer = malloc(sizeof(int) * value);
  printf("partitionOddAndEven %d\n", value);
  work_evenodd(buffer,0,value);
  free(buffer);
}

void work_evenodd(int *arr,int pos,int i)
{
  if(i <= 0)
    {
      print_arr(arr,pos);
      return;
    }
  int ct;
  for(ct = 1;ct <= i;++ct)
    {
      if((ct % 2 == 1 && arr[pos - 1] % 2 == 0) || (ct % 2 == 0 && arr[pos - 1] % 2 == 1))
	{
	  arr[pos] = ct;
	  work_evenodd(arr,pos + 1, i - ct);
	}
    }
}

/*
 * =================================================================
 * This function prints prime number only partitions of a positive integer value
 * For example, if value is 6
 * 2 + 2 + 2 and
 * 3 + 3 are valid partitions
 *
 * 6 is not a valid partition
 * 
 * 2 + 4 and
 * 1 + 5 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

int prime_check(int);
void work_prime(int *,int,int); 

void partitionPrime(int value)
{
  int *buffer = malloc(sizeof(int) * value);
  printf("partitionPrime %d\n", value);
  work_prime(buffer,0,value);
  free(buffer);
}

void work_prime(int *arr,int pos,int i)
{
  int answer;
  if(i <= 0)
    {
      print_arr(arr,pos);
      return;
    }
  int ct;
  for(ct = 1;ct <= i;++ct)
    {
      answer = prime_check(ct);
        if(answer == 1)
	{
	  arr[pos] = ct;
	  work_prime(arr,pos + 1, i - ct);
	}
    }
}

int prime_check(int ct)
{
  int i;
  if(ct < 2)
    {
      return FALSE;
    }
  for(i = 2;i < ct;++i)
    {
      if(ct % i == 0)
	{
	  return FALSE;
	}
    }
  return TRUE;
}
