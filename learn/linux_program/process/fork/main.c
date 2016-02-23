/*
 * fork()����������
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
		/* fork ʧ�ܡ�*/
		perror("fork failed\n");
		exit(1);
	}
/*���ڴ˴�����ʼ�ֲ� */
	
	if (pid == 0)
	{
	/* ���أ��������ӽ��̡�*/
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