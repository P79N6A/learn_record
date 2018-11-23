/*************************************************************************
 > File Name: mother.h
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Wed 21 Nov 2018 04:05:18 PM CST
 ************************************************************************/

#ifndef PERF_ROBOT_PERF_MOTHER_H
#define PERF_ROBOT_PERF_MOTHER_H
#pragma once

#include "msg_define.h"

#include <signal.h>
#include <mqueue.h>
#include <string>
#include <vector>

#include <event2/event.h>
#include <event2/listener.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>

#include <glog/logging.h>


// 虎妈定义
// 虎妈启动若干熊孩子线程发起压力，管理汇总子线程数据
namespace perf_robot {

typedef struct MqStruct {
    mqd_t mq;
    struct sigevent sigev;
    std::string name;   // "perf_mq_$pid"

    MqStruct(): mq(-1) {}

} MqStruct_t;

class NaughtyKid;
class Mother {

    friend void OnMessageFromChildWrapper(int fd, short event, void *argc);
    friend void OnUpdateWrapper(int fd, short event, void *argc);
    friend void OnNewCmdClientAcceptWrapper(evconnlistener *listener, evutil_socket_t fd,
                                            struct sockaddr *sock, int socklen, void *argc);
    friend void OnCmdReadWrapper(struct bufferevent *bev, void *argc);
    friend void OnCmdErrorWrapper(struct bufferevent *bev, short event, void *argc);

public:

    Mother();

    ~Mother();

    // 初始化环境，call before StartLoop
    int Init(pid_t);
    // 启动事件循环，阻塞
    int StartLoop();
    // 退出循环
    void StopLoop(void);
    // 子线程汇报数据到主线程
    int ReportStat(const ChildReportStat_t &stat, unsigned int prio=1) const;

protected:
    // 接收子线程消息队列回调，信号触发
    void OnMessageFromChild(int fd, short event);
    // 定时器回调，m_event_tv
    void OnUpdate(void);
    // cmd client 连接请求处理
    void OnNewCmdClientAccept(evconnlistener *listener, evutil_socket_t fd,
                                            struct sockaddr *sock, int socklen);
    // cmd client 连接异常处理
    void OnCmdError(struct bufferevent *bev, short event);
    // cmd client 命令处理
    void OnCmdRead(struct bufferevent *bev);

private:
    struct event_base *m_event_base;

    struct event *m_mq_event;
    MqStruct_t m_child_mq;

    struct event *m_timer_event;
    struct timeval m_timer_event_tv;

    evconnlistener *m_cmd_listener;

    std::vector<NaughtyKid*> m_childs;
};
} // namespace perf_robot
#endif //PERF_ROBOT_PERF_MOTHER_H
