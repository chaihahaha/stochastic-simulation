#include<stdio.h>
#include "mt19937ar.h"
double uniform(double a, double b)
{
  return (b - a) * genrand_real2() + a;
}
void test_uniform(void)
{
  int i;
  unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
  init_by_array(init, length);
  printf("\n1000 outputs of uniform(2, 4)\n");
  for (i=0; i<100; i++) {
    printf("%10.8f ", uniform(2, 4));
    if (i%5==4) printf("\n");
  }
}
enum Species {A, B, C, Error};
enum Species species_distribution(void)
{
  double Array[3] = {0.5, 0.6, 1};
  double rand_num = genrand_real2();
  if(rand_num < Array[0])
    {
      return A;
    }
  else if(rand_num < Array[1])
    {
      return B;
    }
  else if(rand_num < Array[2])
    {
      return C;
    }
  return Error;
}
void test_reproduction(int drawings)
{
  int Array[3] = {0};
  for(int i=0; i < drawings; i++)
    {
      enum Species rand_species = species_distribution();
      if(rand_species == A)
    Array[0]++;
      else if(rand_species == B)
    Array[1]++;
      else if(rand_species == C)
    Array[2]++;
    }
  printf("\n Probablistic distribution percentage:\n");
  for(int i=0; i < 3; i++)
    {
      printf(" %.2lf%% ", 100 * Array[i]/(double)drawings);
    }

  printf("\n");
  printf("\n Accumulative distribution percentage:\n");
  for(int i=1; i < 3; i++)
    {
      Array[i] += Array[i - 1];
    }
  for(int i=0; i < 3; i++)
    {
      printf(" %.2lf%% ", 100 * Array[i]/(double)drawings);
    }
  printf("\n");
}
int main(void)
{
  printf("\n2) Generation of uniform random numbers between A and B\n");
  test_uniform();
  printf("\n3) Reproduction of discrete empirical distributions\n");
  printf("\n a)\n");
  printf("\n 1000 drawings:\n");
  test_reproduction(1000);
  printf("\n 1000 000 drawings:\n");
  test_reproduction(1000000);
  return 0;
}

