/************************************************************************
	> File Name: find_repeat_num.c
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Wed 15 Feb 2017 10:39:43 AM CST
 ************************************************************************/

/*
一个大小为n的数组，里面的数都属于范围[0,
n-1]，有不确定的重复元素，找到至少一个重复元素，要求O(1)空间和O(n)时间。
* */

#include<stdio.h>

int find_repeat_num(int *ary, int len)
{
	int i;
	for (i = 0; i < len; ++i) {
		int index = (ary[i] >= len)? ary[i] - len : ary[i];
		if (ary[index] > len)
			return index;
		else
			ary[index] += len;
	}
}

void pritf_repeat_num(int *ary, int len)
{
	int i;
	for (i = 0; i < len; ++i) {
		int index = ary[i] % len;
		ary[index] += len;
	}
	for (i=0; i < len; ++i) {
		printf("%d : %d\n", i, ary[i]/len);
	}
}

int main(void)
{
	int a[] = {0, 1, 3, 3, 4, 7, 6, 7, 8, 5};
	for (int i =0; i < sizeof(a)/sizeof(int); ++i)
		printf("%d ", a[i]);
	printf("\n");

	int b = find_repeat_num(a, sizeof(a)/sizeof(int));
	printf("%d\n",b);

	int a1[] = {0, 1, 3, 3, 4, 7, 6, 7, 8, 5};
	pritf_repeat_num(a1, sizeof(a1)/sizeof(int));
	return 0;
}
