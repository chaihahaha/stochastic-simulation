#include<stdio.h>
/*
#include<math.h>
int my_round(double n)
{
    return (int)(n + 0.5);
}

int fibonacci_double(int n)
{
    double sq5  = sqrt(5);
    double phi  = (sq5 + 1.0)/2.0;
    double phin = pow(phi, n);
    return my_round((phin - pow(-1, n)/phin)/sq5);
}
*/
long long unsigned fibonacci(long long unsigned n)
{
    // 93
    long long unsigned an_2 = 0;
    long long unsigned an_1 = 1;
    long long unsigned an   = 1;
    if( n == 0 )
	return 0;
    if( n == 1 )
	return 1;
    for(long long unsigned i=2; i < n; i++)
    {
	an_2 = an_1;
	an_1 = an;
	an   = an_2 + an_1;
    }
    return an;
}

int main(void)
{
    for(long long unsigned i=0; i < 94; i++)
	printf("%llu  %llu\n", i, fibonacci(i));
    return 0;
}
