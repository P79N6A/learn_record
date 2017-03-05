/*************************************************************************
	> File Name: kmp_match.c
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Tue 28 Feb 2017 03:50:02 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_next(const char *p, int *next)
{
	next[0] = -1;
	int plen = strlen(p);
	int k = -1;
	int j = 0;

	while (j < plen - 1) {
		if (k == -1 || p[j] == p[k]) {
			++k;
			++j;
			next[j] = k;
		} else {
			k = next[k];
		}
	}
}

int next[512] = {0};
int kmp_match(const char *s, const char *p)
{
	int slen = strlen(s);
	int plen = strlen(p);
	int i = 0;
	int j = 0;

	get_next(p, next);

	while (i < slen && j < plen) {
		if (j == -1 || s[i] == p[j]) {
			++j;
			++i;
		} else {
			j = next[j];
		}
	}

	if (j == plen) {
		return (i - j);
	}
	return -1;
}

int main(void)
{
	char *s = "aacaadccc";
	char *p = "aad";
	printf("%d\n", kmp_match(s, p));
	return 0;
}
