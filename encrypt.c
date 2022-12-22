#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 1000000

int decimal(int* A)
{
  int p = 0;
  for (int i = 0; i < 8; i++)
  {
    p = 2 * (A[i] + p);
  }

  return p / 2;
}

int binary(int n)
{
  return n > 0 ? (n % 2) + 10 * (binary(n / 2)) : 0;
}

int len(int n)
{
  int i = 1;
  while(n /= 10) i++;
  
  return i;
}

int main(int narg, char** arg)
{
  srand(time(0));
  
  FILE* data = fopen(arg[1], "r");
  FILE* key = fopen(arg[2], "a");
  FILE* code = fopen(arg[3], "a");

  int bits[MAX];

  int i = 0;
  while (i < 127)
  {
    bits[i] = rand() % 2;
    fprintf(key, "%d", bits[i]);
    i++;
  }

  unsigned char x;
  while(fscanf(data, "%c", &x) != EOF)
  {
    int k = i;
    for (int j = 0; j < 8; j++) 
    {
      bits[i] = bits[i - 1] ^ bits[i - 127];
      i++;
    }

    int d = decimal(bits + k);
    
    int e = d ^ x;

    int b = binary(e);

    int r = len(b);
    
    r = 8 - r;
    while(r--) fprintf(code, "%d", 0);
   
    fprintf(code, "%d", b);
  }

  return 0;
}