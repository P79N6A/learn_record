/*
 * ��ӡϵͳ����������libc�ж����ȫ�ֱ���environ
 * ָ�򻷾�������.
 */

#include <stdio.h>

int main(void)
{
 	extern char **environ;	/* û�а������κ�ͷ�ļ��У�������Ҫ����*/

	int i;
	for (i = 0; environ[i] != NULL; i++)
		printf("%s\n", environ[i]);
	return 0;	
}
