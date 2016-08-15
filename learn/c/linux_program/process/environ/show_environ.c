/*
 * 打印系统环境变量，libc中定义的全局变量environ
 * 指向环境变量表.
 */

#include <stdio.h>

int main(void)
{
 	extern char **environ;	/* 没有包含在任何头文件中，所以需要声明*/

	int i;
	for (i = 0; environ[i] != NULL; i++)
		printf("%s\n", environ[i]);
	return 0;	
}
