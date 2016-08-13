/*
 * 修改环境变量
 */

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	/* char *getenv(const chr *name) 查看环境变量，找不到返NULL */
	printf("PATH=%s\n", getenv("PATH"));
	/* 设置环境变量　*/
	setenv("PATH", "hello", 1);
	printf("PATH=%s\n", getenv("PATH"));
	
	/* 修改的只是当前进程的变量*/
	return 0;
}
