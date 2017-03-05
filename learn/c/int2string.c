/*************************************************************************
	> File Name: int2string.c
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Sun 19 Feb 2017 04:03:36 AM PST
 ************************************************************************/

#include<stdio.h>

void int2string(int num, char *str)
{
	if (num < 0) {
		*str++ = '-';
		num = num * (-1);
	}

	char *pstr = str;

	if (num == 0) *pstr++ = '0';
	while (num > 0) {
		*pstr++ = num % 10 + '0';
		num = num / 10;
	}
	*pstr-- = 0;

	while (str < pstr) {
		char a = *str;
		*str++ = *pstr;
		*pstr-- = a;
	}
}

int main(void)
{
	char str[128];

	int2string(0, str);
	printf("%d  : %s\n", 0, str);
	int2string(1, str);
	printf("%d  : %s\n", 1, str);
	int2string(-1, str);
	printf("%d  : %s\n", -1, str);
	int2string(12, str);
	printf("%d  : %s\n", 12, str);
	int2string(-12, str);
	printf("%d  : %s\n", -12, str);
	int2string(65535, str);
	printf("%d  : %s\n", 65535, str);
	return 0;
}

