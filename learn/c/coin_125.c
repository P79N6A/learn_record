/*************************************************************************
	> File Name: coin_125.c
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Thu 16 Feb 2017 10:29:20 AM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>

/*
* 10元, 1, 2, 5如何组合
* */

void coin_125(int less, char *ary, char *p)
{
	if (less <= 0) {
		if (less == 0) {
			*p = 0;
			printf("%s\n", ary);
		}
		return;
	}

	*p = '1';
	coin_125(less - 1, ary, p + 1);
	*p = '2';
	coin_125(less - 2, ary, p + 1);
	*p = '5';
	coin_125(less - 5, ary, p + 1);
}

int main(void)
{
#define TOTAL 10
	char choic[TOTAL + 1] = {0};
	coin_125(10, choic, choic);
	return 0;
}
