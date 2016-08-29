/*************************************************************************
	> File Name: main.c
	> Author: luchaodong
	> Mail: luchaodong@meizu.com
	> Created Time: 2016年01月19日 星期二 14时42分59秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef CODE_VER
#define CODE_VER 0x1010101
#endif

int main (int argc, char *argv[])
{
	int a;
	int  b = (int)CODE_VER;
	memcpy(&a, &b, 4);
	printf("0x%x\n", a);
	return 0;
}

