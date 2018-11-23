/*************************************************************************
 > File Name: mother.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Wed 21 Nov 2018 05:24:53 PM CST
 ************************************************************************/

#include "mother.h"
#include "common.h"
#include "msg_define.h"
#include "flag.h"
#include "naughty_kid.h"

#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace perf_robot {

void OnMessageFromChildWrapper(int fd, short event, void *argc)
{
    Mother *mother = (Mother*)argc;
    mother->OnMessageFromChild(fd, event);
}

void OnUpdateWrapper(int fd, short event, void *argc)
{
    Mother *mother = (Mother*)argc;
    mother->OnUpdate();
}

void OnNewCmdClientAcceptWrapper(evconnlistener *listener, evutil_socket_t fd,
                                struct sockaddr *sock, int socklen, void *argc)
{
    Mother *mother = (Mother*)argc;
    mother->OnNewCmdClientAccept(listener, fd, sock, socklen);
}

void OnCmdReadWrapper(struct bufferevent *bev, void *argc)
{
    Mother *mother = (Mother*)argc;
    mother->OnCmdRead(bev);
}

void OnCmdErrorWrapper(struct bufferevent *bev, short event, void *argc)
{
    Mother *mother = (Mother*)argc;
    mother->OnCmdError(bev, event);
}

Mother::Mother()
    : m_event_base(NULL),
    m_mq_event(NULL), m_child_mq(),
    m_timer_event(NULL),
    m_cmd_listener(NULL)
{}

Mother::~Mother()
{
    for (auto iter = m_childs.begin(); iter != m_childs.end(); ++iter) {
        (*iter)->Stop();
        delete *iter;
        *iter = NULL;
    }
    if (m_cmd_listener) {
        evconnlistener_free(m_cmd_listener);
    }
    if (m_timer_event) {
        event_free(m_timer_event);
    }
    if (m_mq_event) {
        event_free(m_mq_event);
    }
    if (m_event_base) {
        event_base_free(m_event_base);
    }
    if (m_child_mq.mq != -1) {
        mq_unlink(m_child_mq.name.c_str());
        mq_close(m_child_mq.mq);
    }
}

int Mother::Init(pid_t my_pid)
{
    m_event_base = event_base_new();
    if (!m_event_base) {
        return common::kPerfRetcodeNewBaseEventErr;
    }
    event_base_priority_init(m_event_base, 1);


    // child mq
    char mq_name[256];
    snprintf(mq_name, sizeof(mq_name), "/perf_mq_%d", my_pid);
    m_child_mq.name = std::string(mq_name);

    struct mq_attr attr;
    attr.mq_maxmsg = FLAGS_report_mq_size;
    attr.mq_msgsize = sizeof(ChildReportStat);
    m_child_mq.mq = mq_open(mq_name, O_RDWR|O_CREAT|O_NONBLOCK|O_CLOEXEC, 0666, &attr);
    if (m_child_mq.mq == -1) {
        LOG(ERROR) << "Open child mq error, errono " << errno;
        return common::kPerfRetcodeOpenMqErr;
    }
    LOG(INFO) << "Open child mq : " << m_child_mq.name;

    m_mq_event = event_new(m_event_base, SIGUSR1, EV_SIGNAL |EV_PERSIST, OnMessageFromChildWrapper, this);
    if (!m_mq_event) {
        return common::kPerfRetcodeNewSigEventErr;
    }
    event_add(m_mq_event, NULL);
    m_child_mq.sigev.sigev_notify = SIGEV_SIGNAL;
    m_child_mq.sigev.sigev_signo = SIGUSR1;
    mq_notify(m_child_mq.mq, &m_child_mq.sigev);


    // timer 100ms
    m_timer_event_tv.tv_sec = 0;
    m_timer_event_tv.tv_usec = 100 * 1000;
    m_timer_event = event_new(m_event_base, -1, EV_PERSIST, OnUpdateWrapper, this);
    if (!m_timer_event) {
        return common::kPerfRetcodeNewTimeEventErr;
    }
    evtimer_add(m_timer_event, &m_timer_event_tv);


    // cmd listener
    struct sockaddr_in cmd_sin;
    memset(&cmd_sin, 0, sizeof(cmd_sin));
    cmd_sin.sin_family = AF_INET;
    cmd_sin.sin_addr.s_addr = 0;
    cmd_sin.sin_port = htons(FLAGS_cmd_port);
    m_cmd_listener = evconnlistener_new_bind(m_event_base, OnNewCmdClientAcceptWrapper,
                                            this, LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,
                                            FLAGS_cmd_client_num,
                                            (struct sockaddr *)&cmd_sin, sizeof(struct sockaddr_in));
    if (!m_cmd_listener) {
        return common::kPerfRetcodeNewCmdListenerErr;
    }

    // report stat
    if (FLAGS_datasvr_ip != "" && FLAGS_datasvr_port != 0) {
        LOG(INFO) << "Datacollect svr : " << FLAGS_datasvr_ip << ":" << FLAGS_datasvr_port;
        // TODO
    }

    // Init threads
    uint32_t robot_num_per_child = 0;
    uint32_t robot_remain = 0;
    uint32_t robot_start_id = FLAGS_perf_robot_start_id;
    if (FLAGS_perf_work_thread_num > FLAGS_perf_robot_num) {
        robot_num_per_child = 0;
        robot_remain = FLAGS_perf_robot_num;
    } else {
        robot_num_per_child = FLAGS_perf_robot_num / FLAGS_perf_work_thread_num;
        robot_remain = FLAGS_perf_robot_num % FLAGS_perf_work_thread_num;
    }
    for (int i = 0; i < FLAGS_perf_work_thread_num; ++i) {
        NaughtyKid *child = new NaughtyKid(this, i);
        if (!child) {
            return common::kPerfRetcodeNewKidErr;
        }
        int robot_num = robot_num_per_child;
        if (robot_remain > 0) {
            ++robot_num;
            --robot_remain;
        }
        int ret = child->Init(robot_start_id, robot_num);
        if (ret != common::kPerfRetcodeOk) {
            return ret;
        }
        robot_start_id += robot_num;
        m_childs.push_back(child);
    }

    LOG(INFO) << "perf_robot Init ok, pid " << my_pid;
    return common::kPerfRetcodeOk;
}

int Mother::StartLoop()
{
    // start all childs
    for (auto iter = m_childs.begin(); iter != m_childs.end(); ++iter) {
        int ret = (*iter)->Start();
        if (ret != common::kPerfRetcodeOk) {
            for (; iter >= m_childs.begin(); --iter) {
                (*iter)->Stop();
            }
            return ret;
        }
    }
    event_base_dispatch(m_event_base);
    return common::kPerfRetcodeOk;
}

// 接收子线程消息队列回调，信号触发
void Mother::OnMessageFromChild(int fd, short event)
{
    DLOG(INFO) << "Receive stat from child";

    ChildReportStat_t report;
    uint32_t prio = 0;
    ssize_t len = 0;

    while ((len = mq_receive(m_child_mq.mq, reinterpret_cast<char*>(&report), sizeof(ChildReportStat_t), &prio)) != -1) {
        DLOG(INFO) << "Read mq len : " << len << " prio : " << prio;
        // handle message from child


    }
    if (errno != EAGAIN) {
        LOG(ERROR) << "mq receive error, errno : " << errno;
    }
    mq_notify(m_child_mq.mq, &m_child_mq.sigev);
}

// 定时器回调，m_event_tv
void Mother::OnUpdate(void)
{
    static uint8_t t_count = 0;
    if (++t_count >= 10) {
        //DLOG(INFO) << "Timer";
        t_count = 0;

        MotherSendCmd_t cmd;
        m_childs[0]->SendCmd(cmd);
    }
}

void Mother::OnCmdError(struct bufferevent *bev, short event)
{
    evutil_socket_t fd = bufferevent_getfd(bev);
    if (event & BEV_EVENT_TIMEOUT) {//if bufferevent_set_timeouts() called
        LOG(ERROR) << "Client Timed out! fd=" << fd;
    }
    else if (event & BEV_EVENT_EOF) {
		LOG(INFO) << "Client connection closed! fd=" << fd;
    }
    else if (event & BEV_EVENT_ERROR) {
		LOG(ERROR) << "Client some other error! fd=" << fd;
    }
	else {
		LOG(ERROR) << "Client never get here! fd=" << fd;
	}
    bufferevent_free(bev);
}

void Mother::OnCmdRead(struct bufferevent *bev)
{
    evutil_socket_t fd = bufferevent_getfd(bev);
	struct evbuffer *input = bufferevent_get_input(bev);
	struct evbuffer *output = bufferevent_get_output(bev);
    char buffer[256];
	int read_len = bufferevent_read(bev, buffer,sizeof(buffer));//读取并从缓冲区中移除
	bufferevent_write(bev, buffer, read_len);
	LOG(INFO) << "cliend_" << fd << " send cmd len : "<< read_len;
}

void Mother::OnNewCmdClientAccept(evconnlistener *listener, evutil_socket_t fd,
                                            struct sockaddr *sock, int socklen)
{
#ifndef NDEBUG
    struct sockaddr_in *sock_in = reinterpret_cast<struct sockaddr_in*>(sock);
    ///inet_ntop;
    char *ip = inet_ntoa(sock_in->sin_addr);
    DLOG(INFO) << "New Client_" << fd << " form : " << ip << ":" << sock_in->sin_port;
#endif

	struct bufferevent *bev = bufferevent_socket_new(m_event_base, fd, BEV_OPT_CLOSE_ON_FREE);
    if (!bev) {
        LOG(ERROR) << "Client new bufferevent error";
        return;
    }
    bufferevent_setcb(bev, OnCmdReadWrapper, NULL, OnCmdErrorWrapper, this);
    bufferevent_enable(bev, EV_READ|EV_WRITE|EV_PERSIST);
}

int Mother::ReportStat(const ChildReportStat_t &stat, unsigned int prio) const
{
    int ret = common::kPerfRetcodeOk;
    if (mq_send(m_child_mq.mq, (const char *)&stat, sizeof(ChildReportStat_t), prio) != 0) {
        LOG(ERROR) << "mq send error, errno : " << errno;
        if (errno == EAGAIN) {
            ret = common::kPerfRetcodeChildMqFull;
        } else {
            ret = common::kPerfRetcodeChildMqErr;
        }
    }
    return ret;
}

void Mother::StopLoop(void)
{
    // stop all childs
    for (auto iter = m_childs.begin(); iter != m_childs.end(); ++iter) {
        (*iter)->Stop();
    }
    event_base_loopexit(m_event_base, NULL);
    event_base_loopbreak(m_event_base);
}

} // namespace  perf_robot
