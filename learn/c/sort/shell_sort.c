/*************************************************************************
	> File Name: shell_sort.c
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

void shell_sort(int *array, int len)
{
	int gap;
	for (gap = len >> 1; gap > 0; gap = gap >> 1) {
		// directly insert sort
		int i;
		for (i = gap; i < len; i += gap) {
			int j = i;
			while (j > 0 && array[j] < array[j - gap]) {
				swap(array + j, array + j - gap);
				j -= gap;
			}
		}
	}
}

void shell_sort_1(int *array, int len)
{
	int gap;
	for (gap = len >> 1; gap > 0; gap = gap >> 1) {
		// directly insert sort
		int i;
		for (i = gap; i < len; ++i) {
			int j = i;
			int temp = array[j];
			while (j - gap >= 0 && temp < array[j - gap]) {
				array[j] = array[j - gap];
				j -= gap;
			}
			array[j] = temp;
		}
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

	shell_sort_1(ary, sizeof(ary)/sizeof(int));

	for (i = 0; i < sizeof(ary)/sizeof(int); ++i)
		printf("%d ", ary[i]);
	printf("\n");

	return 0;
}
