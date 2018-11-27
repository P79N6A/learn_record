/*************************************************************************
 > File Name: robot.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Fri 23 Nov 2018 09:51:38 AM CST
 ************************************************************************/

#include "common.h"
#include "robot.h"

namespace perf_robot {

Robot::Robot(const NaughtyKid *master, uint32_t id)
    : m_master(master), m_id(id), m_msg_id(1),
    m_send_msg(),
    m_slot_total_send(0), m_slot_send(0),
    m_fsm(0),
    m_timer(0,TIMER_NUMBER), m_conn_bev(NULL)
{

}

Robot::~Robot()
{
    if (m_conn_bev) {
        bufferevent_free(m_conn_bev);
    }
}

int Robot::Init()
{

    return common::kPerfRetcodeOk;
}

void Robot::OnUpdate(void)
{}



} // namespce  perf_robot
