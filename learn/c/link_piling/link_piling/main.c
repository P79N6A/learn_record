/*************************************************************************
 > File Name: main.c
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Thu 14 Sep 2017 09:40:12 AM CST
 ************************************************************************/

#include<stdio.h>
#include"malloc.h"

int main()
{
	int *p = malloc(sizeof(int));
	*p = 12;
	printf("p = %d\n", *p);
	free(p);
	return 0;
}
