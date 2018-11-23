/*************************************************************************
 > File Name: naughty_kid.h
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Wed 21 Nov 2018 03:54:55 PM CST
 ************************************************************************/

#ifndef PERF_ROBOT_PERF_NAUGHTY_KID_H
#define PERF_ROBOT_PERF_NAUGHTY_KID_H
#pragma once

#include "msg_define.h"
#include "common.h"

#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <vector>

#include <event2/event.h>
#include <event2/listener.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>

#include <glog/logging.h>


// 熊孩子定义
// 熊孩子负责发起一定连接，执行动作更新
namespace perf_robot {

class Thread {
    friend void *ThreadRunWrapper(void *argc);
public:
    Thread();
    virtual ~Thread();
    // create thread and run
    virtual int Start(void);
    // thread process
    virtual void Run(void) = 0;
    // join, wait thread exit
    void Join(void);
    bool isRunning(void) const { return m_thread_id != 0; };
private:
    pthread_t m_thread_id;
};

class Mother;
class Robot; // 具体一个连接管理
class NaughtyKid : public Thread {

    friend void OnChildUpdateWrapper(int fd, short event, void *argc);
    friend void OnRevCmdWrapper(int fd, short event, void *argc);

public:
    NaughtyKid(const Mother *mother, uint16_t kid_id);
    virtual ~NaughtyKid();

    // robot_start_id > 0
    int Init(uint32_t robot_start_id, uint32_t robot_num);

    int Start();

    void Run(void);

    void Stop(void);

    int SendCmd(const MotherSendCmd_t &cmd);
private:
    NaughtyKid(): m_mother(NULL), m_id(0) {}

    void OnUpdate(void);
    void OnRevCmd(int fd);

private:
    const Mother* const m_mother;
    const uint16_t m_id;

    uint32_t m_robot_start_id;
    uint32_t m_robot_num;
    std::vector<Robot*> m_robots;
    common::PerfStat_t m_perf_stat;

    struct event_base *m_event_base;

    struct event *m_timer_event;
    struct timeval m_timer_event_tv;

    // mother --pipe--> child
    struct event *m_cmd_event;
    int m_rev_cmd_fd;
    int m_send_cmd_fd;

};

} // namespace perf_robot
#endif //PERF_ROBOT_PERF_NAUGHTY_KID_H
