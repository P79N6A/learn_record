//
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <assert.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include<event2/listener.h>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

// server define
DEFINE_int32(listen_num, 1024, "listen number");
DEFINE_int32(port, 8888, "listen port");
DEFINE_int32(thread_num, 2, "work threads num");
DECLARE_string(flagfile);

pid_t save_pid(void);
void sigint_cb(int fd,  short event, void *argc);

typedef struct Report_stat
{
    int work_id;
    int send_count;
    Report_stat()
        : work_id(0), send_count(0)
    {};
} Report_stat_t;

typedef struct Worker_thread
{
    //peer loog peer thread
    pthread_t thread_id;        //线程ID
    struct event_base *base;   //事件根基

    // main thread notify new connection
    int notify_receive_fd;
    int notify_send_fd;

    // work thread report stat
    int report_receive_fd;
    int report_send_fd;

    Report_stat_t stat;

	Worker_thread()
        :base(NULL), notify_receive_fd(0), notify_send_fd(0),
        report_receive_fd(0), report_send_fd(0),
		thread_id(0), stat()
    {}
} Worker_thread_t;
Worker_thread_t *g_threads = NULL;
vector<long long> g_workers_stat;

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

	char buffer[2048];
	int read_len = bufferevent_read(bev, buffer,sizeof(buffer));//读取并从缓冲区中移除
	bufferevent_write(bev, buffer, read_len);//echo
	LOG(INFO) << "fd="<< fd << ",echo=" << read_len << ",left="<< (int)evbuffer_get_length(input);

	Worker_thread_t *thread_attr = (Worker_thread_t *)arg;
    ++thread_attr->stat.send_count;

	//假设包格式为 4字节记录了包体总长度，其中长度不包含这4个字节
    while (false) {
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
		//LOG(INFO) << "fd="<< fd << ",total=" << total_len << ",echo=" << pkg_len << ",left="<< (int)evbuffer_get_length(input);
    }
}

void listener_cb(evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sock, int socklen, void *arg)
{
    static int s_lastThreadIndex = 0;//上次处理线程

    //写管道通知该线程fd
    int index = s_lastThreadIndex % FLAGS_thread_num;
	if (write(g_threads[index].notify_send_fd, &fd, sizeof(fd)) != sizeof(fd)) {
		LOG(ERROR) << "Writing to thread notify pipe. fd=" << fd;
	}
	if (EPIPE == errno) {
		LOG(ERROR) << "EPIPE!fd=" << g_threads[index].notify_send_fd;
	}
	++s_lastThreadIndex;
	LOG(INFO) << "Main process notify sub process new connect succ! index=" << index << ",fd="<<fd;
}

//工作线程监听分发线程的事件
void do_add_newconn(int32_t fd, int16_t event, void *arg)
{
    // 接收新建立连接
	Worker_thread_t *thread_attr = (Worker_thread_t *)arg;
	struct event_base *base = thread_attr->base;

    int accept_fd;
    if (read(fd, &accept_fd, sizeof(accept_fd)) != sizeof(accept_fd)) {
	   LOG(ERROR) << "Can't read from newconn pipe";
	   exit(2);
    }

	struct bufferevent *bev = bufferevent_socket_new(base, accept_fd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, read_cb, NULL, error_cb, thread_attr);
    bufferevent_enable(bev, EV_READ|EV_WRITE|EV_PERSIST);
}

// main thread read stat data
void do_collect_stat(int32_t fd, int16_t event, void *arg)
{
    Report_stat_t stat;
    if (read(fd, &stat, sizeof(stat)) != sizeof(stat)) {
	   LOG(ERROR) << "Can't read from stat pipe";
	   exit(2);
    }
    g_workers_stat[stat.work_id] += stat.send_count;
}

// main thread log all threads stat
void do_log_stat(int32_t fd, int16_t event, void *arg)
{
    long long send_count = 0;
    stringstream out;
    for(auto iter = g_workers_stat.begin(); iter != g_workers_stat.end(); ++iter) {
        send_count += *iter;
        out << "id[" << (iter-g_workers_stat.begin()) << "]:" << *iter << ";";
        *iter = 0;
    }
    out << " Total : " << send_count;
    LOG(INFO) << out.str();
}

// worker send stat data
void do_report_stat(int32_t fd, int16_t event, void *arg)
{
	Worker_thread_t *thread_attr = (Worker_thread_t *)arg;
    if (write(thread_attr->report_send_fd, &(thread_attr->stat), sizeof(Report_stat_t)) != sizeof(Report_stat_t)) {
		LOG(ERROR) << "Writing report to pipe. id=" << thread_attr->stat.work_id;
	}
	if (EPIPE == errno) {
		LOG(ERROR) << "EPIPE!fd=" << thread_attr->stat.work_id;
	}
    thread_attr->stat.send_count = 0;
}

void *worker_thread(void *arg)
{
	Worker_thread_t *thread_attr = (Worker_thread_t *)arg;

	thread_attr->base = event_base_new();
	if (NULL == thread_attr->base) {
		 LOG(ERROR) << "Can't allocate event base";
	     exit(1);
	}

	struct event *listen_event = event_new(thread_attr->base, thread_attr->notify_receive_fd, EV_READ|EV_PERSIST, do_add_newconn, thread_attr);
    event_add(listen_event, NULL);

    // report to main_thread
    struct timeval tv =  {0, 100 * 1000}; //100ms
    struct event *timer = event_new(thread_attr->base, -1, EV_PERSIST, do_report_stat, thread_attr);
    evtimer_add(timer, &tv);

    event_base_dispatch(thread_attr->base);

    event_base_free(thread_attr->base);
	return NULL;
}

int init_worker_thread(int threadNum)
{
	g_threads = new struct Worker_thread[threadNum];
	if (NULL == g_threads) {
		LOG(ERROR) << "malloc Worker_thread_t failed!";
		exit(1);
	}
    g_workers_stat = vector<long long>(threadNum);

	for (int i = 0; i < threadNum; i++) {
		int fds[2] = {0};
	    if (pipe(fds)) {
		     LOG(ERROR) << "Can't create notify pipe";
	         exit(1);
		}
		g_threads[i].notify_receive_fd = fds[0];
		g_threads[i].notify_send_fd = fds[1];

        if (pipe(fds)) {
		     LOG(ERROR) << "Can't create report pipe";
	         exit(1);
		}
        g_threads[i].report_receive_fd = fds[0];
        g_threads[i].report_send_fd = fds[1];

        g_threads[i].stat.work_id = i;

	    pthread_attr_t attr;
	    pthread_attr_init(&attr);
	    pthread_create(&g_threads[i].thread_id, &attr, worker_thread, &g_threads[i]);
    }

	return 0;
}

int main(int argc, char *argv[])
{
    if (FLAGS_flagfile == "") {
        FLAGS_flagfile = "./echo.flag";
    }
    FLAGS_log_dir = "./log";
    FLAGS_minloglevel = 2; // warning
	google::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);

	//初始化工作线程池
	init_worker_thread(FLAGS_thread_num);

    // event base
    struct event_base *base = event_base_new();
    assert(base != NULL);

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(FLAGS_port);
    evconnlistener *listener = evconnlistener_new_bind(base, listener_cb, base,
                                                      LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,
                                                      FLAGS_listen_num, (struct sockaddr *)&sin, sizeof(struct sockaddr_in));

    // quit signal
    event_base_priority_init(base, 1);
    struct event *sigint_event = event_new(base, SIGINT, EV_SIGNAL |EV_PERSIST, sigint_cb, base);
    event_add(sigint_event, NULL);

    // report collect
    for (int i = 0; i < FLAGS_thread_num; ++i) {
	    struct event *report_event = event_new(base, g_threads[i].report_receive_fd, EV_READ|EV_PERSIST, do_collect_stat, base);
        event_add(report_event, NULL);
    }

    // report loging
    struct timeval tv =  {1, 0};
    struct event *timer = event_new(base, -1, EV_PERSIST, do_log_stat, base);
    evtimer_add(timer, &tv);

    pid_t pid= save_pid();
	LOG(INFO) << "Start Listening..., pid : " << pid;

    event_base_dispatch(base);

    evconnlistener_free(listener);
    event_base_free(base);
    delete [] g_threads;
	LOG(INFO) << "Finished process...";
    return 0;
}

pid_t save_pid(void)
{
    pid_t pid = getpid();
    ofstream out;
    out.open("./echo_svr.pid", ios::out | ios::trunc);
    out << pid;
    out.close();
    return pid;
}

void sigint_cb(int fd,  short event, void *argc)
{
    LOG(INFO) << "Catch sigint(2), exit svr";

    for (int i = 0; i < FLAGS_thread_num; ++i) {
        event_base_loopexit(g_threads[i].base, NULL);
        event_base_loopbreak(g_threads[i].base);
    }

    struct event_base *base = (struct event_base*)argc;
    event_base_loopexit(base, NULL);
    event_base_loopbreak(base);
}
