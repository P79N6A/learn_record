/*
 * ./server.c
 * C/S, 服务器端，读取客户端的字符，转换为小写并发送回客户端
 * tcp协议
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 4096
#define SERV_PORT 8000

int main(void)
{
	struct sockaddr_in servaddr, cliaddr;
	socklen_t cliaddr_len;
	int listenfd, connfd;
	char buf[MAXLINE];
	char str[INET_ADDRSTRLEN];
	int i, n;
	
	/*IPV4, TCP，protocol略,指定0*/
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(listenfd != -1);

	/*清零结构体*/
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;  	       //IPV4
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  //任意ip
	servaddr.sin_port = htons(SERV_PORT); 	       //端口号
	
	/*绑定端口和IP*/
	assert(\
	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != -1);

	
	/*监听，允许20个客户端处于连接待状态*/
	assert( listen(listenfd, 20) != -1 );
	/*阻塞等待*/

	printf("Accepting connectiins ....\n");

	while (1)
	{
		cliaddr_len = sizeof(cliaddr);
		//三次握手啊啊啊啊啊啊啊啊啊啊啊　udp差别１
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
		

		n = read(connfd, buf, MAXLINE);
		printf("Received from %s at PORT %d\n",
			inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), 
			ntohs(cliaddr.sin_port));

		buf[n] = '\0';
		printf("Receive from client : %s\n", buf);

		for (i=0; i < n; ++i)
			buf[i] = toupper(buf[i]);
		
		write(connfd, buf, n);
		close(connfd);
	}
}


