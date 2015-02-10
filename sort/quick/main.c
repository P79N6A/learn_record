/*
 * /sort/quick/main.c
 * 快速排序实现
 * 20150210 lcd 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * quick_sort   
 * @p_start  起始指针
 * @p_end    结束指针
 *
 * 对输入数组进行快速排序(升序)
 * lcd 20150210
*/
void quick_sort(int *p_start, int *p_end)
{
	int index;
	int *p_small = p_start;
	int *p_big = p_end;

	assert(p_start != NULL);
	assert(p_end != NULL);
	
	if (p_start >= p_end)
		return;

	index = *p_small;

	while ( p_small < p_big )
	{
		while ((p_small < p_big) && (index <= (*p_big)))
			p_big--;

		if (p_small < p_big)
		{
		 	*p_small = *p_big;
			p_small++;
		}

		while ((p_small < p_big) && (index > (*p_small)))
			p_small++;

		if (p_small < p_big)
		{
		 	*p_big = *p_small;
			 p_big++;
		}
	}
	*p_small = index;
	quick_sort(p_start, (int*)(p_small-1));
	quick_sort((int*)(p_big+1), p_end);
}


/**
 * main
 */
int main(void)
{
	int array[] = {4, 3, 6, 1, 5, 2, 7};
	printf("%d %d %d %d %d %d %d \n", array[0], array[1], array[2], array[3], array[4], array[5], array[6]);
	
	quick_sort(array, array+6);
	
	printf("%d %d %d %d %d %d %d \n", array[0], array[1], array[2], array[3], array[4], array[5], array[6]);
	return 0;
}
