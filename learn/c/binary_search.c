/*************************************************************************
	> File Name: binary_search.c
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Thu 16 Feb 2017 01:58:32 PM CST
 ************************************************************************/

#include<stdio.h>

int binary_search(int *a, int n, int val)
{
	int l = 0;
	int r = n - 1;
	while ( l <= r ) {
		int midle = l + ((r - l) >> 1);
		if (a[midle] > val) r = midle - 1;
		else if (a[midle] < val) l = midle + 1;
		else return midle;
	}
	return -1;
}

int main(void)
{
	int a1[] = {1};
	int a[] = {1, 2};
	int a2[] = {1, 2, 3, 4};

	printf("%d : %d\n", 1, binary_search(a1, 1, 1));
	printf("%d : %d\n", 2, binary_search(a1, 1, 2));

	printf("%d : %d\n", 1, binary_search(a, 2, 1));
	printf("%d : %d\n", 2, binary_search(a, 2, 2));
	printf("%d : %d\n", 3, binary_search(a, 2, 3));

	printf("%d : %d\n", 1, binary_search(a2, 4, 1));
	printf("%d : %d\n", 2, binary_search(a2, 4, 2));
	printf("%d : %d\n", 3, binary_search(a2, 4, 3));
	printf("%d : %d\n", 4, binary_search(a2, 4, 4));
	printf("%d : %d\n", 5, binary_search(a2, 4, 5));

	return 0;
}
