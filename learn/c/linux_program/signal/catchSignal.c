
//安装信号处理函数
//按下　ctrl-\可以退出
#include <signal.h>
#include <string.h>
#include <unistd.h>



/* 信号处理函数　*/
void handler(int signum)
{
	char buf[200], *cp;
	int offset;

	strcpy(buf, "Handler : caught signal ");
	cp = buf + strlen(buf); //指向字符结尾
	
	//把信号值转换为字符形式
	if (signum > 100)  //不可能
		offset = 3;
	else if (signum > 10)
		offset = 2;
	else 
		offset = 1;
	
	cp += offset;
	*cp-- = '\0';  //结尾
	
	while (signum > 0)
	{
		*cp-- = (signum % 10) + '0';
		signum /=10;
	}

	strcat(buf, "\n");
	(void)write(2, buf, strlen(buf));

//一些系统处理后会重置，所以需要重装	
//	(void)signal(signum, handler);  //重新安装
}

int main()
{
	(void)signal(SIGINT, handler);  //重新安装

	while (1)
		pause();
	return 0;
	
}
