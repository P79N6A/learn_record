/*************************************************************************
	> File Name: size.c
	> Author: luchaodong
	> Mail: luchaodong@meizu.com
	> Created Time: 2016年01月12日 星期二 10时36分32秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	unsigned char a[10][10];
	int len = sizeof(a);
	int len_1 = sizeof(a[2]);
	printf("a[][] len %d, a[] len %d\n", len, len_1);
	return 0;
}
