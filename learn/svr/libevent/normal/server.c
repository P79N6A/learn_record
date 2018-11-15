/*************************************************************************
 > File Name: server.c
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Wed 14 Nov 2018 08:21:27 PM CST
 ************************************************************************/


#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>

#include<event.h>
#include<event2/listener.h>
#include<event2/bufferevent.h>
//#include<thread.h>

void socket_read_cb(bufferevent *bev,  void *arg)
{
    char msg[4096];

    int len = bufferevent_read(bev, msg, sizeof(msg) - 1);
    msg[len] = '\0';
    printf("server read the data: %s", msg);

    char reply_msg[4096] = "I have recvieced the msg: ";
    strcat(reply_msg + strlen(reply_msg) - 1, msg);
    bufferevent_write(bev, reply_msg, strlen(reply_msg));
}

void socket_event_cb(bufferevent* bev, short events, void* arg)
{
    if (events & BEV_EVENT_EOF) {
        printf("connection closed\n");
    } else if (events & BEV_EVENT_ERROR) {
        printf("some other error\n");
    }
    bufferevent_free(bev);
}

// client 连接过来，event 已经处理好accept，回调函数时传来新建的socketfd
void listener_cb(evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sock, int socklen, void *arg)
{
    printf("Accept a client %d\n", fd);
    struct event_base *base = (event_base*)arg;

    // 新连接分配缓冲区
    struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);

    bufferevent_setcb(bev, socket_read_cb, NULL, socket_event_cb, NULL);
    bufferevent_enable(bev, EV_READ| EV_PERSIST);
}

int main(int argc, char* argv[])
{
    //evthread_use_pthreads();

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(8888);

    struct event_base* base = event_base_new();

    evconnlistener *listener = evconnlistener_new_bind(base, listener_cb, base,
                                                      LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,
                                                      10, (struct sockaddr *)&sin, sizeof(struct sockaddr_in));

    // loop
    event_base_dispatch(base);

    evconnlistener_free(listener);
    event_base_free(base);

    return 0;
}
