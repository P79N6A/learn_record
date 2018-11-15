#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <Attr_API.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <fcntl.h>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <map>

#define LISTEN_BACKLOG 1024

DEFINE_int32(port, 19988, "LISTEN_PORT");
DEFINE_int32(threadNum, 8, "threadNum");

typedef struct Worker_thread
{
    pthread_t thread_id;        //线程ID
    struct event_base *base;   //事件根基
    //struct event notify_event;
    int notify_receive_fd;   
    int notify_send_fd;     
    //CQ new_conn_queue;    //连接队列

	Worker_thread()
    {
		base = NULL;
		notify_receive_fd = 0;
		notify_send_fd = 0;
		thread_id = 0;
    }
} Worker_thread_t;

Worker_thread_t *g_threads = NULL;

void write_cb(struct bufferevent *bev, void *arg) 
{

}

void error_cb(struct bufferevent *bev, short event, void *arg)
{
    evutil_socket_t fd = bufferevent_getfd(bev);
    if (event & BEV_EVENT_TIMEOUT) {//if bufferevent_set_timeouts() called
        LOG(ERROR) << "Timed out! fd=" << fd;
    }
    else if (event & BEV_EVENT_EOF) {
		LOG(INFO) << "connection closed";
    }
    else if (event & BEV_EVENT_ERROR) {
		LOG(ERROR) << "some other error! fd=" << fd;
    }
	else
	{
		LOG(ERROR) << "never get here! fd=" << fd;
	}
    bufferevent_free(bev);
}

void read_cb(struct bufferevent *bev, void *arg)
{
    //int len;
    evutil_socket_t fd = bufferevent_getfd(bev);
	struct evbuffer *input = bufferevent_get_input(bev);
	struct evbuffer *output = bufferevent_get_output(bev);

	//假设包格式为 4字节记录了包体总长度，其中长度不包含这4个字节
    while (true)
    {
	    char buffer[2048];

		int total_len = (int)evbuffer_get_length(input);
		if (total_len < 4)//缓冲区总长度太小
		{
			return;
		}
		
		int head_len = 0;//包头存放长度
		int copy_len = (int)evbuffer_copyout(input, &head_len, 4);//读4个字节，但是不从缓冲区移除
		if (copy_len != 4)
		{
			LOG(ERROR) << "fd="<< fd << " evbuffer_copyout invailed! copy_len="<< copy_len;
			close(fd);
			return;
		}
		
		int pkg_len = ntohl(head_len);//得到包体长度
		if (total_len < pkg_len + 4)//缓冲区长度不够整个包长
		{
	    	return; 
		}

		if (pkg_len <= 4)
		{
			LOG(ERROR) << "fd="<< fd << " pkg maybe invailed! pkg_len="<< pkg_len << ",total=" << total_len;
			//close(fd);
			evbuffer_drain(input, total_len);//移除缓冲区所有的内容
			return;
		}

		//int read_len = bufferevent_read(bev, buffer, pkg_len);//读取并从缓冲区中移除
		evbuffer_remove(input, buffer, pkg_len + 4);//读取并从缓冲区中移除
		//bufferevent_write(bev, buffer, pkg_len);//echo
		evbuffer_add(output, buffer, pkg_len + 4);
		Attr_API(3130908, 1);
		//LOG(INFO) << "fd="<< fd << ",total=" << total_len << ",echo=" << pkg_len << ",left="<< (int)evbuffer_get_length(input);
    }
}

int g_lastThreadIndex = 0;//上次处理线程
void do_accept(evutil_socket_t listener, short event, void *arg)
{
    //struct event_base *base = (struct event_base *)arg;
    int fd;
    struct sockaddr_in sin;
    socklen_t slen = sizeof(sin);
    fd = accept(listener, (struct sockaddr *)&sin, &slen);
    if (fd < 0) {
		LOG(ERROR) << "accept() failed!";
        return;
    }

	evutil_make_socket_nonblocking(fd);
    int index = g_lastThreadIndex % FLAGS_threadNum;
	
	if (write(g_threads[index].notify_send_fd, &fd, sizeof(fd)) != 1) //写管道通知该线程fd
	{
		LOG(ERROR) << "Writing to thread notify pipe. fd=" << fd;
	}

	if (EPIPE == errno)
	{
		LOG(ERROR) << "EPIPE!fd=" << g_threads[index].notify_send_fd;
	}

	g_lastThreadIndex++;
	LOG(INFO) << "Main process notify sub process succ! index=" << index << ",fd="<<fd;
}

//工作线程监听分发线程的事件
void notifyEventHandler(int32_t fd, int16_t event, void *arg) 
{
    LOG(INFO) << "NotifyEventHandler";
	struct event_base *base = (struct event_base *)arg;
	
    int accept_fd;
    if (read(fd, &accept_fd, sizeof(accept_fd)) != sizeof(accept_fd))
    {	
	   LOG(ERROR) << "Can't read from libevent pipe";
	   exit(2);
    }	

	struct bufferevent *bev = bufferevent_socket_new(base, accept_fd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, read_cb, NULL, error_cb, arg);
    bufferevent_enable(bev, EV_READ|EV_WRITE|EV_PERSIST);
}

void *worker_thread(void *args)
{
	Worker_thread_t *thread_attr = (Worker_thread_t *)args;
	
	thread_attr->base = event_base_new();
	if (NULL == thread_attr->base) 
	{
		 LOG(ERROR) << "Can't allocate event base";
	     exit(1);
	}
    
	struct event *listen_event = event_new(thread_attr->base, thread_attr->notify_receive_fd, EV_READ|EV_PERSIST, notifyEventHandler, (void*)thread_attr->base);
    event_add(listen_event, NULL);
    event_base_dispatch(thread_attr->base);

	return NULL;
}

int InitWorkerThread(int threadNum)
{
	g_threads = new struct Worker_thread[threadNum];
	if (NULL == g_threads)
	{
		LOG(ERROR) << "malloc Worker_thread_t failed!";
		exit(1);
	}

	for (int i = 0; i < threadNum; i++) 
	{
		int fds[2] = {0};
	    if (pipe(fds)) 
		{
		     LOG(ERROR) << "Can't create notify pipe";
	         exit(1);
		}
		g_threads[i].notify_receive_fd = fds[0];
		g_threads[i].notify_send_fd = fds[1];

	    pthread_attr_t attr;
	    pthread_attr_init(&attr);
	    pthread_create(&g_threads[i].thread_id, &attr, worker_thread, &g_threads[i]);
    }   

	return 0;
}

int main(int argc, char *argv[])
{
	google::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);

	//初始化工作线程池
	InitWorkerThread(FLAGS_threadNum);
	
    int ret;
    evutil_socket_t listener;
    listener = socket(AF_INET, SOCK_STREAM, 0);
    assert(listener > 0);
    evutil_make_listen_socket_reuseable(listener);

    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(FLAGS_port);

	ret = bind(listener, (struct sockaddr *)&sin, sizeof(sin));
    if (ret < 0) {
        LOG(ERROR) << "bind() failed! ret=" << ret;
        return 1;
    }

	ret = listen(listener, LISTEN_BACKLOG);
    if (ret < 0) {
		LOG(ERROR) << "listen() failed! ret=" << ret;
        return 1;
    }

	LOG(INFO) << "Start Listening...";

    evutil_make_socket_nonblocking(listener);

    struct event_base *base = event_base_new();
    assert(base != NULL);
    struct event *listen_event;
    listen_event = event_new(base, listener, EV_READ|EV_PERSIST, do_accept, (void*)base);
    event_add(listen_event, NULL);
    event_base_dispatch(base);

	LOG(INFO) << "Finished process...";
    return 0;
}
