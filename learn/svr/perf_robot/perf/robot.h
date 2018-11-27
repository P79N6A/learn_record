/*************************************************************************
 > File Name: robot.h
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Fri 23 Nov 2018 09:53:14 AM CST
 ************************************************************************/

#ifndef PERF_ROBOT_PERF_ROBOT_H
#define PERF_ROBOT_PERF_ROBOT_H
#pragma once

#include "common.h"
#include <stdint.h>
#include <map>
#include <vector>
#include <cassert>
#include <unistd.h>
#include <sys/time.h>

#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>

#include <glog/logging.h>

namespace perf_robot {

class NaughtyKid;

typedef struct RobotUserData {
    // define your date
    uint64_t session_id;

    RobotUserData()
    : session_id(0)
    {}
} RobotUserData_t;


class Robot {
public:
    // index 0 - TIMER_NUMBER
    static const uint8_t TIMER_NUMBER = 8;

public:

    Robot(const NaughtyKid *master, uint32_t id);
    ~Robot();

    int Init();

    // call by timer
    void OnUpdate(void);

private:

    void ResetTimer(uint8_t index) {
        assert(index < TIMER_NUMBER);
        m_timer[index] = 0;
    }
    bool Wait(uint8_t index, uint32_t time_wait) {
        assert(index < TIMER_NUMBER);
        struct timeval tv;
        //TODO performance ??
        gettimeofday(&tv, NULL);
        uint64_t tus = tv.tv_sec * 1000 * 1000 + tv.tv_usec;
        if (m_timer[index] < tus) {
            if (m_timer[index] == 0) {
                m_timer[index] = tus + time_wait;
            }
            return false;
        } else {
            m_timer[index] = 0;
            return true;
        }
    }

    // slot 开端更新发包数，上一轮没发完继续留到这轮
    // 记录压力个过大
    void UpdateSlotSendCount(void);

    // true 是有返回的参数发包，false 本轮任务完成，不能发
    bool GetNewMsgId(uint32_t &msg_id) {
        if (m_slot_total_send > m_slot_send) {
            msg_id = m_msg_id++;
            m_slot_send++;
            return true;
        }
        return false;
    }

    // 判断是否有包等待rsp
    bool hasMsgWaitRsp(void) {
        return m_send_msg.size();
    }

    // 收包后传递msgid，统计时延
    void RevMsgRsp(uint32_t msg_id) {
        if (m_send_msg.count(msg_id) == 1) {
            // 判断是否超时
            //auto it = m_send_msg.find(msg_id);
            //if (it != m_send_msg.end()) {
                ///
                //it->second;
                //m_send_msg.erase(it);
                //
        } else {
            //超时已经清理了
        }
    }

    // 统计超时包
    void UpdateTimeoutMsg(void);



private:
    RobotUserData_t m_data;

private:
    // 机器所属
    const NaughtyKid* const m_master;

    uint32_t m_id;

    uint32_t m_msg_id;
    // 发包后保存m_msg_id-> 发包时间，判断超时，计算时延
    // <m_msg_id, time_send_point(us)>
    std::map<uint32_t, uint64_t> m_send_msg;

    // 当前区间预计发送的包数
    // 发包位置： 每次update（异步）和收到回包（一般是同步下）
    uint32_t m_slot_total_send;
    // 当前区间已经发送的包数
    uint32_t m_slot_send;

    // finite-state machine, 场景时记录下一个执行状态
    // switch-case
    uint8_t m_fsm;

    // 定时器
    // reset : 0
    // 第一次(如果值为0)设置对应定时器为 now + waittime
    // 之后进来检查是否达到，达到返回true，并清 0
    // 否则返回false，不修改保存值
    std::vector<uint64_t> m_timer;

    // 连接事件对象
    struct bufferevent* m_conn_bev;
};

} // namespace perf_robot
#endif //PERF_ROBOT_PERF_ROBOT_H
