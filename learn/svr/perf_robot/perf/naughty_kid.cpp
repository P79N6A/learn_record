/*************************************************************************
 > File Name: naughty_kid.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Wed 21 Nov 2018 05:26:28 PM CST
 ************************************************************************/

#include "naughty_kid.h"
#include "mother.h"

namespace perf_robot {

void *ThreadRunWrapper(void *argc)
{
    Thread *kid = static_cast<Thread*>(argc);
    kid->Run();
    return NULL;
}

Thread::Thread(void)
    : m_is_stop(false), m_thread_id(0)
{}

Thread::~Thread(void)
{
    if (m_thread_id != 0) {
        pthread_join(m_thread_id, NULL);
    }
}

int Thread::Start()
{
    pthread_attr_t attr;
	pthread_attr_init(&attr);
	int ret = pthread_create(&m_thread_id, &attr,ThreadRunWrapper, this);
    if (ret != 0) {
        LOG(ERROR) << "Create thread error, errono : " << errno;
    }
    return ret;
}

NaughtyKid::NaughtyKid(const Mother *mother, uint16_t kid_id)
    : m_mother(mother), m_id(kid_id),
    m_robot_start_id(0), m_robot_num(0), m_robots()
{
}

NaughtyKid::~NaughtyKid()
{
}

int NaughtyKid::Init(uint32_t robot_start_id, uint32_t robot_num)
{
    m_robot_start_id = robot_start_id;
    m_robot_num = robot_num;
    return common::kPerfRetcodeOk;
}

// start thread
int NaughtyKid::Start()
{
    if (m_robot_start_id == 0) {
        return common::kPerfRetcodeChildNotInit;
    }
    if (Thread::Start() != 0) {
        return common::kPerfRetcodeCreateThreadErr;
    }
    return common::kPerfRetcodeOk;
}

void NaughtyKid::Run(void)
{
    LOG(INFO) << "CHILD run" << "num " << m_robot_num << " " << m_robot_start_id;
    while (!isStop()) {
        sleep(1);
        ChildReportStat_t stat;
        m_mother->ReportStat(stat, m_id);
    }
    LOG(INFO) << "CHILD QUIT";
    // start event loop
}

} // namespace perf_robot
