#include <stdio.h>
#include <stdlib.h>
#define MAX 1000000

int decimal(FILE* text, int* A)
{
  int p = 0;
  for (int i = 0; i < 8; i++)
  {
    p = 2 * (A[i] + p);
  }
  
  fprintf(text, "%c", p / 2);

  return 0;
}

int main(int narg, char** arg)
{
  FILE* key = fopen(arg[1], "r");
  FILE* code = fopen(arg[2], "r");
  FILE* msg = fopen(arg[3], "a");

  int xor[MAX];
  char bits[MAX];
  
  int i = 0;
  while (fscanf(key, "%c", &bits[i]) != EOF) 
  {
    bits[i] -= '0';
    i++;
  }

  char p;
  int n = 0;
  while(fscanf(code, "%c", &p) != EOF)
  {
    p -= '0';
    bits[i] = bits[i - 1] ^ bits[i - 127];
    xor[n] = bits[i] ^ p;
    i++;
    n++;
  }

  for (int j = 0; j < n; j = j + 8) decimal(msg, xor + j);

  return 0;
}