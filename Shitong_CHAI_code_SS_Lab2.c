/*****************************************************
* Shitong_CHAI_code_SS_Lab2.c                        *
*                                                    *
* The Lab #2 experiment program source code.         *
*                                                    *
*****************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "mt19937ar.h"
typedef int (*fun_ptr)();
typedef double (*fun_ptr_double)();

/************************** Section 2 ***************************/
double uniform(double a, double b)
{
/*
* :argument 
*       a,b are the endpoints of an interval [a,b]. 
* :return  
*       A random number in the interval [a,b].
* :usage
*       To generate a uniformly distributed random number.
*/

  return (b - a) * genrand_real2() + a;
}
void test_uniform(void)
{
/*
* :usage
*       To generate 1000 uniformly distributed random numbers and 
*       print them to the screen.
*/
  int               i;
  unsigned long     init[4] = {0x123, 0x234, 0x345, 0x456};
  unsigned long     length  = 4;
  init_by_array(init, length);
  printf("\n1000 outputs of uniform(2, 4)\n");
  for (i=0; i<100; i++) {
    printf("%10.8f ", uniform(2, 4));
    if (i%5==4) printf("\n");
  }
}
/************************** Section 3 ***************************/

int species_distribution(void)
{
/*
* :return  
*       A random number which corresponds to a species.
* :usage
*       To generate a species randomly with a given C.D.F.
*/
  double    Array[3] = {0.5, 0.6, 1};
  double    rand_num = genrand_real2();
  for(int i=0; i<3; i++)
    {
        if(rand_num < Array[i])
        {
            return i;
        }
    }
  return -1;
}
int another_distribution(void)
{
/*
* :return  
*       A random number which corresponds to a class.
* :usage
*       To generate a class randomly with a given repartition 
*       function which is a simulated distribution.
*/
    double      Array[5] = {0.2, 0.3, 0.5, 0.8, 1};
    double      rand_num = genrand_real2();
    for(int i=0; i<5; i++)
    {
        if(rand_num < Array[i])
        {
            return i;
        }
    }
    return -1;
}
void test_reproduction(int drawings, int size, fun_ptr distribution)
{
/*
* :argument 
*       drawings is the number of samples, size is the size of the
*       given discrete repartition function array, distribution is
*       the distribution from which random classes are generated. 
* :usage
*       To collect the statistical distribution of the generated
*       random classes and print them to the screen.
*/
    int *Array = malloc(size * sizeof(int));
    for(int i=0; i < size; i++)
    {
        Array[i] = 0;
    }
    for(int i=0; i < drawings; i++)
    {
        int rand_species = distribution();
        for(int j=0; j < size; j++)
            if(rand_species == j)
                Array[j]++;
    }
    printf("\n Probabilistic distribution percentage:\n");
    for(int i=0; i < size; i++)
    {
        printf(" %.2lf%% ", 100 * Array[i]/(double)drawings);
    }

    printf("\n");
    printf("\n Accumulative distribution(repartition) percentage:\n");
    for(int i=1; i < size; i++)
    {
        Array[i] += Array[i - 1];
    }
    for(int i=0; i < size; i++)
    {
        printf(" %.2lf%% ", 100 * Array[i]/(double)drawings);
    }
    printf("\n");
}
/************************** Section 4 ***************************/
double negative_exponential(double M_coeff)
{
/*
* :argument 
*       M_coeff is the coefficient M in the formula of negative 
*       exponential distribution function. 
* :return  
*       A random number following the PDF: f(x)=exp(-x/M)/M.
* :usage
*       To generate a negative exponentially distributed 
*       random number.
*/
    double      rand_num = genrand_real2();
    return -M_coeff*log(1-rand_num);
}
void test_negative_exponential(int drawings)
{
/*
* :argument 
*       drawings is the number of samples.
* :usage
*       To collect the data of generated negative 
*       exponentially distributed numbers and print
*       it to the screen.
*/
    int     Test20bins[20]={0};
    int     rand_num;
    for(int i=0; i<drawings; i++)
    {
        rand_num = negative_exponential(10);
        if((int)rand_num<=19 && (int)rand_num>=0)
        {
            Test20bins[(int)rand_num]++;
        }
    }
    printf("\n%d drawings(P.D.F.):", drawings);
    printf("\n");
    for(int i=0; i<20; i++)
    {
        printf("%.2lf%% ", 100 * (double)Test20bins[i]/(double)drawings);
    }
    printf("\n");
}
/************************** Section 5 ***************************/
double norm_box_muller(void)
{
/*
* :return  
*       A random number following standard normal distribution.
* :usage
*       To generate a random number following the distribution N(0,1).
*/
    double rn1 = genrand_real2();
    double rn2 = genrand_real2();
    return cos(2 * M_PI * rn2) * sqrt(-2*log(rn1));
}  
double norm_mu10_sigma3(void)
{
/*
* :return  
*       A random number following normal distribution N(10,3²).
* :usage
*       To generate a random number following the 
*       distribution N(10,3²) based on the formula: X~N(0,1),
*       D(σX+μ)=σ², E(σX+μ)=μ.
*/
    double rn = norm_box_muller();
    return 3 * rn + 10;
}
void test_norm(int drawings, fun_ptr_double distribution)
{
/*
* :argument 
*       drawings is the number of samples, distribution
*       is the random distribution from where to samples
*       data. 
* :usage
*       To collect data about the generated random numbers
*       and print it to the screen.
*/
    int     array[7] = {-3, -2, -1, 0, 1, 2, 3};
    int     count[6] = {0};
    for(int i=0; i < drawings; i++)
    {
        double rand_num = distribution();
        for(int i=0; i < 6; i++)
        {
            if(rand_num >= array[i] && rand_num < array[i+1])
                count[i]++;
        }
    }
    printf("\n%d drawings:\n", drawings);
    for(int i=0; i < 6; i++)
    {
        printf("%.2lf ", (double)count[i]/(double)drawings);
    }
    printf("\n");
}    

int main(void)
{
    /************************** Section 2 ***************************/
    printf("\n2) Generation of uniform random numbers between A and B\n");
    test_uniform();

    /************************** Section 3 ***************************/
    printf("\n3) Reproduction of discrete empirical distributions\n");

    printf("\n a)\n");
    printf("\n 1000 drawings:\n");
    test_reproduction(1000, 3, species_distribution);
    printf("\n 1000 000 drawings:\n");
    test_reproduction(1000000, 3, species_distribution);

    printf("\n b)\n");
    printf("\n 1000 drawings:\n");
    test_reproduction(1000, 5, another_distribution);
    printf("\n 1000 000 drawings:\n");
    test_reproduction(1000000, 5, another_distribution);
    
    /************************** Section 4 ***************************/
    printf("\n4) Reproduction of continuous distributions\n");
    test_negative_exponential(1000);
    test_negative_exponential(1000000);
    
    /************************** Section 5 ***************************/
    printf("\n5) Simulating non reversible distribution laws\n");
    test_norm(1000, norm_box_muller);
    test_norm(1000000, norm_box_muller);
    printf("\nGaussian distribution with an average of 10 and with a standard deviation at 3");
    test_norm(1000, norm_mu10_sigma3);
    
    /////////// 6 /////////////
    //http://savannah.gnu.org/projects/gsl
    //https://www.gnu.org/software/gsl/
  return 0;
}

