#include <stdio.h>
#include <stdlib.h>
#define N 100
typedef int (*fun_ptr)();

int power(int num, int index)
{
	if (index == 0)
		return 1;
	else if (index == 1)
		return num;
	else
		return num * power(num, index - 1);
}
int middle_square_pseudo_rand(int seed)
{
	int digits[4];
	int square = seed * seed;
	int ans = 0;
	for (int i = 2; i < 6; i++)
	{
		digits[i - 2] = (square / power(10, i)) % 10;
	}
	
	for (int i = 0; i < 4; i++)
	{
		ans += digits[i] * power(10, i);
	}
	return ans % power(10, 4);
}
void main_middle_square(int seed)
{
	int middleSquare = seed, square;
    printf("\nSeed: %d\n", seed);
	for (int i = 0; i < 10; i++)
	{
		square = middleSquare * middleSquare;
		middleSquare = middle_square_pseudo_rand(middleSquare);
		printf("%2d : %08d %04d\n", i, square, middleSquare);
	}
		
}
void coin_tossing(int experiment_scale)
{
	int positive_count = 0, negative_count = 0;
	printf("coin tossing experiment. runs: %d\n", experiment_scale);
	for (int i = 0; i < experiment_scale; i++)
	{
		if (rand() % 2 == 1)
			positive_count++;
		else
			negative_count++;
	}
	printf("positive possibility: %lf\n", (double)positive_count / (positive_count + negative_count));
	printf("\n");
}
void regular_dice_simulation(int faces, int experiment_scale)
{
	printf("regular dice simulation experiment. faces: %d runs: %d\n", faces, experiment_scale);
	int count[faces], sum = 0;
	for (int j = 0; j < faces; j++)
	{
		count[j] = 0;
	}

	for (int i = 0; i < experiment_scale; i++)
	{
		for (int j = 0; j < faces; j++)
		{
			if (rand() % faces == j)
				count[j]++;
		}
		
	}
	for (int j = 0; j < faces; j++)
	{
		sum += count[j];
	}
	for (int j = 0; j < faces; j++)
	{
		printf("face: %d  possibility: %lf\n", j + 1, (double)count[j] / sum);
	}
	printf("\n");
}

int intRand(int a, int c, int m, int iterations, int seed)
{
    int x = seed;
    printf("\n");
    for(int i=0; i < iterations; i++)
    {
        x = (a * x + c) % m;
        printf("%d ", x);
    }
    return x;
}

double floatRand(int a, int c, int m, int iterations, int seed)
{
    int x = seed;
    double y;
    printf("\n");
    for(int i=0; i < iterations; i++)
    {
        x = ((a * x + c) % m);
        y = x/(double)m;
        printf("%lf ", y);
    }
    return y;
}

int LFSR(int iterations, int seed)
{
    
    int x = seed%16;
    printf("\n");
    for(int i=0;i<iterations;i++)
    {
        
        x = ((((x^(x<<1))<<2)&8)|((x>>1)&15));
        printf("%d ",x);
    }
    
    return x;
}

int Array[N];
void initShuffledGen(fun_ptr GX)
{
    for(int i=0;i<N;i++)
    {
        Array[i] = GX();
    }
}

int shuffledGen(fun_ptr GX, fun_ptr GY)
{
    int index = GY()%N;
    int RN = Array[index];
    Array[index] = GX();
    return RN;
}

int main()
{
    // 1)
    printf("\n1) Random numbers generated using middle square algorithm:\n");
    main_middle_square(1234); 
    
    // 2)
    printf("\n2) Random numbers generated using different seeds:\n");
    main_middle_square(4100); 
	main_middle_square(1324); 
    main_middle_square(1301);
    main_middle_square(3141);
    
    // 3)
    // man 3 rand
    
    // 4)
    printf("\n4) Coin tossing simulation results:\n");
    coin_tossing(10);
	coin_tossing(100);
	coin_tossing(1000);
    
    // 5)
    printf("\n5) Regular dice simulation results:\n");
	regular_dice_simulation(6, 100);
	regular_dice_simulation(6, 1000);
	regular_dice_simulation(10, 10);
	regular_dice_simulation(10, 100);
	regular_dice_simulation(10, 1000);
	regular_dice_simulation(10, 1000000);
    
    // 6,7)
    printf("\n6)7) Random numbers generated using LCG:");
    intRand(5, 1, 16, 32, 5);
    floatRand(5, 1, 16, 32, 5);
    
    // 8)
    printf("\n\n8) Random numbers generated using different a,c and m:");
    intRand(13, 3, 32, 32, 17);
    floatRand(13, 3, 32, 32, 17);
    printf("\n\n");
    
    printf("9)\n\
    Smart tuples and seeds rules:\n\
    1. c and m are relatively prime.\n\
    2. a-1 is divisible by all prime factors of m.\n\
    3. If m is a mutiple of 4, then a-1 is also.\n");
    
    printf("10)\n\
    Scientific libraries implementing up to date PRNGs:\n\
    1. ISAAC\n\
    2. SIMD-oriented Fast Mersenne Twister(SFMT)\n");
    
    printf("11)\n\
    Statistical libraries able to test the quality of pseudo random number sources:\
    1. TestU01\n\
    2. NIST Statistical Test Suite\n");
    
    // 12)
    printf("\n\n12) Random numbers generated using LFSR with x^4+x+1 as characteristic polynomial:"); 
    LFSR(30, 8);
    
    // 13)
    printf("\n\n13) Random numbers generated using given shuffling principle:\n");
    initShuffledGen(rand);
    for(int i=0;i<20;i++)
    {
        printf("%d ", shuffledGen(rand, rand));
    }
    printf("\n");
    system("pause");
}
