/*************************************************************************
	> File Name: select_sort.c
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Fri 10 Feb 2017 04:36:18 AM PST
 ************************************************************************/

#include<stdio.h>

void swap(int *a, int *b)
{
	int c = *a;
	*a = *b;
	*b = c;
}


void select_sort(int *array, int len)
{
	int i;
	for (i = 0; i < len; ++i) {
		int j;
		int index = i;
		for (j = i + 1; j < len; ++j) {
			if (array[index] > array[j]) index = j;
		}
		swap(array + i, array + index);
	}
}

int main (void)
{
	int ary[] = {73, 66, 33, 12, 20, 56, 97, 12, 43, 71, 12, 50, 43, 48, 43,
	      4, 27, 89, 2, 27, 66, 35, 81, 89, 82, 10, };
	int i;
	for (i = 0; i < sizeof(ary)/sizeof(int); ++i)
		printf("%d ", ary[i]);
	printf("\n");

	select_sort(ary, sizeof(ary)/sizeof(int));

	for (i = 0; i < sizeof(ary)/sizeof(int); ++i)
		printf("%d ", ary[i]);
	printf("\n");

	return 0;
}
