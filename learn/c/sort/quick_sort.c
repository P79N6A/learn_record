/*************************************************************************
	> File Name: quick_sort.c
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Fri 10 Feb 2017 04:36:18 AM PST
 ************************************************************************/

#include<stdio.h>

// if a == b , it cause error!! --> 0
// 不一定高效， 别用了
void swap(int *a, int *b)
{
	if (a == b) {
		printf("error\n");
		return;
	}
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void swap1(int *a, int *b)
{
	int c = *a;
	*a = *b;
	*b = c;
}

void set_pvote(int *array, int begin, int end)
{
	int dv = end - begin;
	if ( dv < 2 ) return;

	int midle = begin + dv/2;

	if (array[end] < array[midle]) swap1(array + end, array + midle);
	if (array[end] < array[begin]) swap1(array + end, array +begin);
	if (array[midle] > array[begin]) swap1(array + midle, array + begin);
}

void quick_sort(int *array, int begin, int end)
{
	if (end <= begin) return;

	set_pvote(array, begin, end);

	int *pvote = array + begin;
	int l = begin + 1;
	int r = end;
	while (l < r) {
		if (array[l] < *pvote) {
			++l;
		} else if (array[r] >= *pvote) {
			--r;
		} else if (l < r) {
			swap1(array + l, array + r);
		}
	}

	--l;
	swap1(pvote, array + l);
	quick_sort(array, begin, l);
	quick_sort(array, r, end);
}

int main (void)
{
	int ary[] = {73, 66, 33, 12, 20, 56, 97, 12, 43, 71, 12, 50, 43, 48, 43,
	      4, 27, 89, 2, 27, 66, 35, 81, 89, 82, 10, };
	int i;
	for (i = 0; i < sizeof(ary)/sizeof(int); ++i)
		printf("%d ", ary[i]);
	printf("\n");

	quick_sort(ary, 0, sizeof(ary)/sizeof(int) - 1);

	for (i = 0; i < sizeof(ary)/sizeof(int); ++i)
		printf("%d ", ary[i]);
	printf("\n");

	return 0;
}
