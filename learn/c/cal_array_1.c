/*************************************************************************
	> File Name: cal_array_1.c
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Tue 14 Feb 2017 04:45:29 PM CST
 ************************************************************************/

/*
*
给定一数组a[N]，我们希望构造数组b [N]，
其中b[j]=a[0]*a[1]…a[N-1] /a[j]，在构造过程中，不允许使用除法：
要求O（1）空间复杂度和O（n）的时间复杂度；
除遍历计数器与a[N]
b[N]外，不可使用新的变量（包括栈临时变量、堆空间和全局静态变量等）；
**/

#include<stdio.h>

#define A_LEN 5

int main(void)
{
	int a[A_LEN] = {1, 3, 5, 7, 9};
	int b[A_LEN];
	int i;

	for (i = 0; i < A_LEN; ++i)
		b[i] = 1;

	for (i = 1; i < A_LEN; ++i) {
		b[i] *= b[i-1] * a[i-1];
	}

	for (i = A_LEN - 1; i > 0; --i) {
		b[i] *= b[0];
		b[0] *= a[i];
	}

	printf("aa \n");
	for (i = 0; i < A_LEN; ++i)
		printf("%d ", a[i]);
	printf("\n");

	printf("bb \n");
	for (i = 0; i < A_LEN; ++i)
		printf("%d ", b[i]);
	printf("\n");

	return;
}
