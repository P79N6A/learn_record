/*
 * �޸Ļ�������
 */

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	/* char *getenv(const chr *name) �鿴�����������Ҳ�����NULL */
	printf("PATH=%s\n", getenv("PATH"));
	/* ���û���������*/
	setenv("PATH", "hello", 1);
	printf("PATH=%s\n", getenv("PATH"));
	
	/* �޸ĵ�ֻ�ǵ�ǰ���̵ı���*/
	return 0;
}
