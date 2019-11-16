/*****************************************************
* Shitong_CHAI_code_SS_Lab3.c                        *
*                                                    *
* The Lab #3 experiment program source code.         *
* To compile: gcc -O2 Shitong_CHAI_code_SS_Lab3.c    *
* mt19937ar.h mt19937ar.c                            *
*                                                    *
*****************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "mt19937ar.h"

double uniform(double a, double b)
{
    /*
     * :argument 
     *       a,b are the endpoints of an interval [a,b]. 
     * :return  
     *       A random number in the interval [a,b].
     * :usage
     *       To generate a uniformly distributed 
     *       random number.
     */

    return (b - a) * genrand_real2() + a;
}
double compute_pi(unsigned long long points)
{
    
    /*
     * :argument
     *     points: the number of points
     *             generated to get Pi.
     * :return
     *  The value of Pi computed with Monte Carlo 
     *     method.
     * :usage
     *     Call the function with drawings, the bigger
     *     drawings is, the more precise the answer 
     *     will be.
     */
    double x, y;
    unsigned long long    counter=0;
    for(unsigned long long i=0; i < points; i++)
    {
        x = genrand_real2();
        y = genrand_real2();
        if((x * x + y * y) < 1)
            counter++;
    }
    return 4 * (double)counter/(double)points;

}
void print_converging_process(unsigned long long c, unsigned long long d, unsigned long long b)
{
    /*
     * :argument
     *     c: the number of printing cycles.
     *     d: the drawings of one printing cycle.
     *     b: the basic drawings.
     * :usage
     *     print the process of converging.
     */
    double x, y;
    unsigned long long    counter=0;
    for(unsigned long long i=0; i < b; i++)
    {
        x = genrand_real2();
        y = genrand_real2();
        if((x * x + y * y) < 1)
            counter++;
    }
    printf("drawings: %llu, pi ~ %lf\n", b, 4 * (double)counter/(double)(b));
    for(unsigned long long i=1; i<=c; i++)
    {
        for(unsigned long long j=0; j<d; j++)
        {
            x = genrand_real2();
            y = genrand_real2();
            if((x * x + y * y) < 1)
                counter++;
        }
        printf("drawings: %llu, pi ~ %lf\n", i*d+b, 4 * (double)counter/(double)(i*d+b));
    }
}
double *independent_experiments(unsigned long long n, unsigned long long points)
{
    /*
     * :argument 
     *     n: the number of independent experiments
     *     points: the number of points generated.
     * :return
     *     array storing n experiment results
     * :usage
     *     Run MC simulation n times with fixed
     *     points generated.
     */
    double *results = malloc(n * sizeof(double));
    printf("Running %llu independent experiments\n", n);
    for(unsigned long long i=0; i < n; i++)
    {
	results[i] = compute_pi(points);
    }
    return results;
}
double average(double *a, unsigned long long n)
{
    /*
     * :argument
     *     n: the number of independent experiments 
     *     a: array storing n experiment results 
     * :return 
     *     mean value of array a
     * :usage
     *     compute the mean value of array a
     */
     double summary=0;
     for(unsigned long long i=0; i < n; i++)
     {
         summary += a[i];
     }
     return summary/n;
}
void print_array_mean(double *a, unsigned long long n)
{
    /*
     * :argument
     *     a: array storing n experiment results
     *     n: the number of independent experiments
     * :return
     *     nothing
     * :usage
     *     Print the array and mean (average)
     */

    for(unsigned long long i=0; i < n; i++)
    {
	printf("Experiment %llu: %lf\n", i, a[i]);

    }
    printf("Final result(average): %lf\n", average(a,n));
    
}
double sigma2(double *a, double mean, unsigned long long n)
{
    /*
     * :argument
     *     n: the number of independent experiments 
     *     mean: the average value of array a
     *     a: array storing n experiment results 
     * :return 
     *     estimate without bias of sigma^2 variance
     * :usage
     *     compute the estimated variance of array a 
     */
     double summary=0;
     for(unsigned long long i=0; i < n; i++)
     {
         summary += (a[i]-mean) * (a[i]-mean);
     }
     return summary/(n-1);
}
double tn_1_distribution(unsigned long long n)
{
    if(n<=0)
        return -1;
    double t_n[35]={-1, 12.706, 4.303, 3.182, 2.776, 
    2.571, 2.447, 2.365, 2.308, 2.262, 2.228, 2.201, 
    2.179, 2.160, 2.145, 2.131, 2.120, 2.110, 2.101, 
    2.093, 2.086, 2.080, 2.074, 2.069, 2.064, 2.060, 
    2.056, 2.052, 2.048, 2.045, 2.042, 2.021, 2.000, 
    1.980, 1.960}; 
    if(n<=30)
        return t_n[n];
    else if(n<=40)
        return t_n[31];
    else if(n<=80)
        return t_n[32];
    else if(n<=120)
        return t_n[33];
    else
        return t_n[34];
}
double confidence_radius(double *a, double mean, unsigned long long n)
{
    /*
     * :argument
     *     n: the number of independent experiments 
     *     mean: the average value of array a
     *     a: array storing n experiment results 
     * :return 
     *     confidence radius
     * :usage
     *     compute the confidence radius of n 
     *     independent experiments 
     */
    
    return tn_1_distribution(n)*sqrt(sigma2(a, mean, n)/n);
}

void print_confidence_interval_level(double *a, unsigned long long n)
{
    /*
     * :argument
     *     n: the number of independent experiments 
     *     a: array storing n experiment results 
     * :return 
     *     nothing
     * :usage
     *     print confidence interval and confidence 
     *     level
     */
    double mean = average(a, n);
    double R = confidence_radius(a, mean, n);
    printf("Mean value: %lf\n", mean);
    printf("Confidence interval: [%lf, %lf]\n", mean-R,mean+R);
    printf("Confidence level: 95%%\n");
}

int main()
{
    init_genrand(1);
    printf("1) Compute Pi with the Monte Carlo method:\n");
    printf("1000 points:\n");
    printf("Pi ~ %lf\n", compute_pi(1000));
    printf("1000 000 points:\n");
    printf("Pi ~ %lf\n", compute_pi(1000000));
    printf("1000 000 000 points:\n");
    printf("Pi ~ %lf\n", compute_pi(1000000000));
    
    // print_converging_process(6, 10000000000, 100000);

    printf("2) n independent experiments\n");
    double *results = independent_experiments(10, 1000000);
    print_array_mean(results, 10);

    printf("3) Computing of confidence intervals around the mean\n");
    double *results2 = independent_experiments(10, 1000000);
    print_confidence_interval_level(results2, 10);
    /*
1) Compute Pi with the Monte Carlo method:
1000 points:
Pi ~ 3.172000
1000 000 points:
Pi ~ 3.139400
1000 000 000 points:
Pi ~ 3.141541
5000 000 000 points:
Pi ~ 3.141635
2) n independent experiments
Running 10 independent experiments
Experiment 0: 3.140680
Experiment 1: 3.142196
Experiment 2: 3.140428
Experiment 3: 3.139236
Experiment 4: 3.138304
Experiment 5: 3.140536
Experiment 6: 3.143248
Experiment 7: 3.143300
Experiment 8: 3.142524
Experiment 9: 3.139664
Final result(average): 3.141012
3) Computing of confidence intervals around the mean
Running 10 independent experiments
Mean value: 3.141803
Confidence interval: [3.140998, 3.142609]
Confidence level: 95%

    */
}
