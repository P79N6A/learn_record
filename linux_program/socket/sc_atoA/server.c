/*
 * ./server.c
 * C/S, �������ˣ���ȡ�ͻ��˵��ַ���ת��ΪСд�����ͻؿͻ���
 * tcpЭ��
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
	
	/*IPV4, TCP��protocol��,ָ��0*/
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(listenfd != -1);

	/*����ṹ��*/
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;  	       //IPV4
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  //����ip
	servaddr.sin_port = htons(SERV_PORT); 	       //�˿ں�
	
	/*�󶨶˿ں�IP*/
	assert(\
	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != -1);

	
	/*����������20���ͻ��˴������Ӵ�״̬*/
	assert( listen(listenfd, 20) != -1 );
	/*�����ȴ�*/

	printf("Accepting connectiins ....\n");

	while (1)
	{
		cliaddr_len = sizeof(cliaddr);
		//�������ְ�����������������������udp���
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


