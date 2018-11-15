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
#include <event2/bufferevent.h>
#include <event2/buffer.h>

void event_cb(struct bufferevent* bev, short event, void *arg)
{
    if (event  & BEV_EVENT_EOF) {
        printf("Connection closed\n");
    } else if (event &  BEV_EVENT_ERROR) {
        printf("some other error");
    } else if (event& BEV_EVENT_CONNECTED) {
        printf("new client connect\n");
        return ;
    }
    bufferevent_free(bev);

    struct event *ev = (struct event*)arg;
    event_free(ev);
}

void server_msg_cb(struct bufferevent* bev, void *arg)
{
    char msg[1024];

    int len = bufferevent_read(bev, msg, sizeof(msg) - 1);
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

    struct bufferevent* bev = (struct bufferevent *)arg;
    bufferevent_write(bev, msg, len);
}

int main(int argc, char* argv[])
{
    if ( argc < 3 ) {
        printf("%s ip port\n\n", argv[0]);
        return -1;
    }

    struct event_base*  base = event_base_new();

    //socket
    struct bufferevent* bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);
    // stdin
    struct event* ev_cmd = event_new(base, STDIN_FILENO, EV_READ | EV_PERSIST, cmd_msg_cb, (void*)bev);

    event_add(ev_cmd, NULL);

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    inet_aton(argv[1], &server_addr.sin_addr);

    bufferevent_socket_connect(bev, (struct sockaddr *)&server_addr,  sizeof(server_addr));
    bufferevent_setcb(bev, server_msg_cb, NULL, event_cb, (void*)ev_cmd);
    bufferevent_enable(bev,  EV_READ| EV_PERSIST);

    // loop
    event_base_dispatch(base);

    event_base_free(base);
    printf("Finished \n");
    return 0;
}
