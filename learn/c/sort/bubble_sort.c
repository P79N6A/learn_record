/*************************************************************************
	> File Name: bubble.c
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Thu 09 Feb 2017 02:55:16 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

void swap(int *a, int *b)
{
	if (a == b) return;
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void bubble_sort(int *array, int len)
{
	int j;
	int last_index = len;
	while (last_index) {
		int index = last_index;
		last_index = 0;
		for (j = 1; j < index; ++j) {
			if (array[j] < array[j - 1]) {
				swap(array + j, array + j - 1);
				last_index = j;
			}
		}
	}
}

int main(void)
{
	int array[] = {-1, -2, -3, -4, -4, -4, 98, 11, 32, 232, 1, 3, 5, 4, 2, 6, 0, -1, -2, -3, -1, -3};
	int i;

	printf("Array\n");
	for (i = 0; i < sizeof(array)/sizeof(int); ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");

	printf("Bubble sort\n");
	bubble_sort(array, sizeof(array)/sizeof(int));
	for (i = 0; i < sizeof(array)/sizeof(int); ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");

	return 0;
}
