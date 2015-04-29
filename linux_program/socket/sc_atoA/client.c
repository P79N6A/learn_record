/*
 * ./client.c
 * c/s,客户端，发送大写字母到服务器，读取服务器转换为小写字符并显示
 * tcp协议
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 4096
#define SERV_PORT 8000

int main(int argc, char *argv[])
{
	struct sockaddr_in servaddr;
	char buf[MAXLINE];
	int sockfd, n;
	char *str;

	if ( argc != 2 )
	{
		fputs("Usage : ./client message \n", stderr);
		exit(1);
	}

	str = argv[1];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(sockfd != -1);

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);


	assert(\
	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) >= 0);

	write(sockfd, str, MAXLINE);

	n = read(sockfd, buf, MAXLINE);
	buf[n] = '\0';
	
	printf("Respon from server : ");
	printf("%s\n", buf);
	close(sockfd);
	return 0;
}
