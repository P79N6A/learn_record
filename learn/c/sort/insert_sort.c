/*************************************************************************
	> File Name: insert_sort.c
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

void insert_sort(int *array, int len)
{
	int index;
	for (index = 1; index < len; ++index) {
		int i = index;
		while (i > 0 && array[i] < array[i - 1]) {
			swap(array + i, array + i - 1);
			--i;
		}
	}
}

void insert_sort_1(int *array, int len)
{
	int index;
	for (index = 1; index < len; ++index) {
		int i = index;
		int temp = array[i];
		while (i > 0 && temp < array[i - 1]) {
			array[i] = array[i - 1];
			--i;
		}
		array[i] = temp;
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

	insert_sort_1(ary, sizeof(ary) / sizeof(int));

	for (i = 0; i < sizeof(ary)/sizeof(int); ++i)
		printf("%d ", ary[i]);
	printf("\n");

	return 0;
}
