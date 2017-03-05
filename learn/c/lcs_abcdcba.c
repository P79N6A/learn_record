/*************************************************************************
	> File Name: lcs_abcdcba.c
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Sun 19 Feb 2017 04:24:22 AM PST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

/*
LCS 最长公共子序列
最长子串是串的一个连续的部分，最长子序列则是从不改变序列的顺序，
而从序列中去掉任意的元素而获得新的序列；
子串中字符的位置必须是连续的，子序列则可以不必连续。
* */

char is_huiwen(char *str, int len)
{
	if (len <= 1) return 0;
	char *pend = str + len - 1;
	while (str < pend) {
		if (*str++ != *pend--) return 0;
	}
	return 1;
}

void get_lcs(char *str1, int len1, char *str2, int len2)
{
	int arr[50][50] = {{0}};
	int i = 0;
	int j = 0;

	for (i = 1; i <= len1; ++i) {
		for (j = 1; j <= len2; ++j) {
			if (str1[i - 1] == str2[j - 1]) {
				arr[i][j] = arr[i - 1][j - 1] + 1;
			} else {
				arr[i][j] = (arr[i-1][j] >= arr[i][j-1])?
					arr[i-1][j]:arr[i][j-1];
			}
		}
	}

	for (i = 0; i <= len1; ++i) {
		for (j = 0; j <= len2; ++j) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

	for (i = len1, j = len2; i >= 1 && j >= 1;) {
		if (str1[i - 1] == str2[i - 1]) {
			printf("%c", str1[i - 1]);
			--i;
			--j;
		} else {
			if (arr[i][j-1] >= arr[i-1][j]) j--;
			else i--;
		}
	}
	printf("\n");
}

int main(void)
{
	char *a0 = "abcdcba";
	char *a1 = "abcdcbd";
	printf("%s %d\n", a0, is_huiwen(a0, 7));
	printf("%s %d\n", a1, is_huiwen(a1, 7));

	char *a2 = "dbcdcba";
	printf("%s || %s\n", a1, a2);
	get_lcs(a1, 7, a2, 7);
	return 0;
}
