/*************************************************************************
 > File Name: client.c
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Wed 14 Nov 2018 07:39:25 PM CST
 ************************************************************************/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <event.h>
#include <event2/util.h>

int tcp_connect_server(const char* server_ip, int port)
{
    int sockfd, status, save_errno;
    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    status = inet_aton(server_ip, &server_addr.sin_addr);

    if (status == 0) {
        errno = EINVAL;
        return -1;
    }// the server ip is not valid value

    sockfd = ::socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        return -1;
    }

    status = ::connect(sockfd, (struct sockaddr *)&server_addr,  sizeof(server_addr));
    if (status == -1) {
        save_errno = errno;
        ::close(sockfd);
        errno = save_errno;
        return -1;
    }

    evutil_make_socket_nonblocking(sockfd);
    return sockfd;
}

void socket_read_cb(int fd, short events, void *arg)
{
    char msg[1024];

    int len = read(fd, msg, sizeof(msg) - 1);
    if (len <= 0) {
        perror("Read fail");
        exit(1);
    }
    msg[len] = '\0';
    printf("recv %s from server \n", msg);
}


void cmd_msg_cb(int fd, short events, void *arg)
{
    char msg[1024];
    int len = read(fd, msg, sizeof(msg));
    if (len <= 0) {
        perror("read fail");
        exit(1);
    }
    int sockfd = *((int*)arg);
    write(sockfd, msg, len);
}

int main(int argc, char* argv[])
{
    if ( argc < 3 ) {
        printf("%s ip pprt\n\n", argv[0]);
        return -1;
    }

    int sockfd = tcp_connect_server(argv[1], atoi(argv[2]));
    if (sockfd == -1) {
        perror("tcp connect error");
        return -1;
    }
    printf("Connect to server successful\n");

    struct event_base*  base = event_base_new();

    struct event* ev_sockfd = event_new(base, sockfd, EV_READ | EV_PERSIST, socket_read_cb, NULL);
    event_add(ev_sockfd, NULL);

    struct event* ev_cmd = event_new(base, STDIN_FILENO, EV_READ | EV_PERSIST, cmd_msg_cb, (void*)&sockfd);
    event_add(ev_cmd, NULL);

    // loop
    event_base_dispatch(base);

    printf("Finished \n");
    return 0;
}
