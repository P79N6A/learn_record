
//��װ�źŴ�����
//���¡�ctrl-\�����˳�
#include <signal.h>
#include <string.h>
#include <unistd.h>



/* �źŴ�������*/
void handler(int signum)
{
	char buf[200], *cp;
	int offset;

	strcpy(buf, "Handler : caught signal ");
	cp = buf + strlen(buf); //ָ���ַ���β
	
	//���ź�ֵת��Ϊ�ַ���ʽ
	if (signum > 100)  //������
		offset = 3;
	else if (signum > 10)
		offset = 2;
	else 
		offset = 1;
	
	cp += offset;
	*cp-- = '\0';  //��β
	
	while (signum > 0)
	{
		*cp-- = (signum % 10) + '0';
		signum /=10;
	}

	strcat(buf, "\n");
	(void)write(2, buf, strlen(buf));

//һЩϵͳ���������ã�������Ҫ��װ	
//	(void)signal(signum, handler);  //���°�װ
}

int main()
{
	(void)signal(SIGINT, handler);  //���°�װ

	while (1)
		pause();
	return 0;
	
}
