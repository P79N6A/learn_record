/*
 * fork()　函数测试
 */


#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid;
	char *message;
	int n;
	
	pid = fork();
	if (pid < 0)
	{
		/* fork 失败　*/
		perror("fork failed\n");
		exit(1);
	}
/*　在此处程序开始分叉 */
	
	if (pid == 0)
	{
	/* 返回０，处于子进程　*/
		message = "This is the child\n";
		n = 6; 
	}
	else
	{
		message = "This is the parent\n";
		n = 3;
	}
	for(; n > 0; n--)
	{
		printf("%s\n", message);
		sleep(1);
	}
	return 0;
}
