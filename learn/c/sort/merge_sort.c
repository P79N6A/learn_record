/*************************************************************************
	> File Name: merge_sort.c
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Fri 10 Feb 2017 04:36:18 AM PST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

/*
* !!! array1 + len1 == array2
* */
void merge_array(int *array1, int len1, int *array2, int len2, int *pbuffer)
{

	if (array1 + len1 != array2) {
		printf("call function error!!\n");
		return;
	}

	int i = 0;
	int j = 0;
	int k = 0;
	while (i < len1 && j < len2) {
		if (array1[i] < array2[j])
			pbuffer[k++] = array1[i++];
		else
			pbuffer[k++] = array2[j++];
	}

	while (i < len1) pbuffer[k++] = array1[i++];
	while (j < len2) pbuffer[k++] = array2[j++];
	while (k--) array1[k] = pbuffer[k];
}

void _merge_sort(int *array, int start, int end, int *pbuffer)
{
	if (start < end) {
		int midle = start + ((end - start) >> 1);
		_merge_sort(array, start, midle, pbuffer);
		_merge_sort(array, midle + 1, end, pbuffer);
		merge_array(array + start, (midle - start + 1),
				array + midle + 1, (end - midle), pbuffer);
	}
}

char merge_sort(int *array, int len)
{
	int *pbuffer = (int*)malloc(sizeof(int)*len);
	if (!pbuffer) return -1;

	_merge_sort(array, 0, len - 1, pbuffer);

	free(pbuffer);
	return 0;
}

int main (void)
{
	int ary[] = {73, 66, 33, 12, 20, 56, 97, 12, 43, 71, 12, 50, 43, 48, 43,
	      4, 27, 89, 2, 27, 66, 35, 81, 89, 82, 10, };
	int i;
	for (i = 0; i < sizeof(ary)/sizeof(int); ++i)
		printf("%d ", ary[i]);
	printf("\n");

	merge_sort(ary, sizeof(ary)/sizeof(int));

	for (i = 0; i < sizeof(ary)/sizeof(int); ++i)
		printf("%d ", ary[i]);
	printf("\n");

	return 0;
}
