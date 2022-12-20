#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>

int max2(int a, int b)
{
	int max = a;

	if (max < b)
		max = b;

	return max;
}

int max3(int a, int b, int c)
{
	int max = a;

	if (max < b)
		max = b;
	if (max < c)
		max = c;

	return max;
}

int max3(int, int, int);

int main(void)
{
	printf("%d\n", max2(4, 2));

	int a = 5, b = 9, c = 8;
	int max = max3(a, b, c);
	printf("%d\n", max);

	return 0;
}

int max3(int a, int b, int c)
{
	int max = a;

	if (max < b)
		max = b;
	if (max < c)
		max = c;

	return max;
}