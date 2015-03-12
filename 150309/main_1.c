//20150309
//luchaodong

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void swap(int *a, int *b)
{
	*a = *a + *b;
    	*b = *a - *b;
   	*a = *a - *b;
}


void rotate(int nums[], int n, int k) 
{
	int i, j;
	int *p1, *p2;
	int temp;

	if(n <= k || k <= 0)
		return;
	
	i = n / k;
	p1 = &nums[n-k];

	if (i >= 2)
	{
		p2 = p1 - k;
		while (--i)
		{
			for (j = 0; j < k; ++j)
				swap(&p1[j], &p2[j]);
			p1 = p2;
			p2 = p1 - 1;
		}
	}

	i = n % k;
	while (i--)
	{
		p1 -= 1;
		temp = *p1;
		for (j = 0; j < k; ++j)
			swap(&p1[j], &p1[j+1]);
		p1[j] = temp;
	}
}

int main()
{
	int nums[] = {1, 2, 3, 4, 5, 6, 7};
	int i;
	for (i = 0; i < 7; ++i)
		printf("%d\t", nums[i]);
	printf("\n");


	rotate(nums, 7, 3);
	for (i = 0; i < 7; ++i)
		printf("%d\t", nums[i]);
	printf("\n");

	return 0;
}

