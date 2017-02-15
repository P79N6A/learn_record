/*************************************************************************
	> File Name: heap_sort.c
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

void min_heap_fix_up(int *a, int i)
{
	int j, temp;
	temp = a[i];
	j = (i - 1) / 2; // parent node
	while (j >= 0 && i != 0) {
		if (a[j] <= temp)
			break;

		// continue up
		a[i] = a[j];
		i = j;
		j = (i - 1) / 2;
	}
	a[i] = temp;
}


void min_heap_fix_up1(int *a, int i)
{
	int j;
	for (j = (i -1)/2; (j>=0 && i!=0) && a[i]<a[j]; i = j, j = (i-1)/2)
		swap(a+i, a+j);
}

void min_heap_add(int *a, int n, int nb)
{
	a[n] = nb;
	min_heap_fix_up(a, n);
}

void min_heap_fix_down(int *a, int i, int n)
{
	int j, temp;
	temp = a[i];
	j = 2 * i + 1;// child node
	while (j < n) {
		if (j + 1 < n && a[j + 1] < a[j]) //right child node good
			++j;

		if (a[j] >= temp)
			break;

		// continue donw
		a[i] = a[j];
		i = j;
		j = 2 * i + 1;
	}
	a[i] = temp;
}

void min_heap_del(int *a, int n)
{
	swap(a, a + n -1); // delete a[0]
	min_heap_fix_down(a, 0, n - 1);
}

void make_min_heal(int *a, int n)
{
	int i;
	for (i = n/2-1; i >= 0; --i)
		min_heap_fix_down(a, i, n);
}

void min_heap_sort(int *a, int n)
{
	make_min_heal(a, n);

	int i;
	for (i = n - 1; i >= 1; --i) {
		swap(a, a + i);
		min_heap_fix_down(a, 0, i);
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

	min_heap_sort(ary, sizeof(ary)/sizeof(int));

	for (i = 0; i < sizeof(ary)/sizeof(int); ++i)
		printf("%d ", ary[i]);
	printf("\n");

	return 0;
}
