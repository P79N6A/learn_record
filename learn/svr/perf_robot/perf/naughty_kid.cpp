/*************************************************************************
 > File Name: naughty_kid.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Wed 21 Nov 2018 05:26:28 PM CST
 ************************************************************************/

#include "naughty_kid.h"
#include "mother.h"
#include "flag.h"
#include "robot.h"

#include <arpa/inet.h>

namespace perf_robot {

void OnChildUpdateWrapper(int fd, short event, void *argc)
{
    NaughtyKid *obj = (NaughtyKid*)argc;
    obj->OnUpdate();
}

void OnRevCmdWrapper(int fd, short event, void *argc)
{
    NaughtyKid *obj = (NaughtyKid*)argc;
    obj->OnRevCmd(fd);
}

NaughtyKid::NaughtyKid(const Mother *mother, uint16_t kid_id)
    : m_mother(mother), m_id(kid_id),
    m_robot_start_id(0), m_robot_num(0), m_robots(), m_perf_stat(),
    m_event_base(NULL), m_timer_event(NULL), m_cmd_event(NULL)
{
}

NaughtyKid::~NaughtyKid()
{
    if (m_timer_event) {
        event_free(m_timer_event);
    }
    if (m_cmd_event) {
        event_free(m_cmd_event);
    }
    if (m_event_base) {
        event_base_free(m_event_base);
    }
    close(m_send_cmd_fd);
    close(m_rev_cmd_fd);

    for(auto iter = m_robots.begin(); iter != m_robots.end(); ++iter) {
        delete *iter;
        *iter = NULL;
    }
}

int NaughtyKid::Init(uint32_t robot_start_id, uint32_t robot_num)
{
    m_robot_start_id = robot_start_id;
    m_robot_num = robot_num;

    m_event_base = event_base_new();
    if (!m_event_base) {
        return common::kPerfRetcodeNewBaseEventErr;
    }
    event_base_priority_init(m_event_base, 3);


    m_timer_event_tv.tv_sec = 0;
    m_timer_event_tv.tv_usec = FLAGS_thread_update_interval * 1000;
    m_timer_event = event_new(m_event_base, -1, EV_PERSIST, OnChildUpdateWrapper, this);
    if (!m_timer_event) {
        return common::kPerfRetcodeNewTimeEventErr;
    }
    evtimer_add(m_timer_event, &m_timer_event_tv);
    event_priority_set(m_timer_event, 1);


    // rev cmd from mother
    int fds[2] = {0};
    if (pipe(fds)) {
		LOG(ERROR) << "Can't create cmd pipe";
        return common::kPerfRetcodeCreatePipeErr;
    }
    m_rev_cmd_fd = fds[0];
    m_send_cmd_fd = fds[1];
	m_cmd_event=  event_new(m_event_base, m_rev_cmd_fd, EV_READ|EV_PERSIST, OnRevCmdWrapper, this);
    event_add(m_cmd_event, NULL);
    event_priority_set(m_timer_event, 2);


    memset(&m_server_addr, 0, sizeof(m_server_addr));
    m_server_addr.sin_family = AF_INET;
    m_server_addr.sin_port = htons(FLAGS_server_port);
    inet_aton(FLAGS_server_ip.c_str(), &m_server_addr.sin_addr);

    // init robot
    uint32_t robot_id = robot_start_id;
    int ret;
    for (int i = 0; i < robot_num; ++i) {
        Robot* robot = new Robot(this, robot_id);
        if (robot == NULL) {
            return common::kPerfRetcodeNewRobotErr;
        }
        int ret = robot->Init();
        if (ret != common::kPerfRetcodeOk) {
            return ret;
        }
        ++robot_id;
    }

    return common::kPerfRetcodeOk;
}

int NaughtyKid::SendCmd(const MotherSendCmd_t &cmd)
{
    return write(m_send_cmd_fd,&cmd , sizeof(MotherSendCmd_t));
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
    LOG(INFO) << "Child run, id " << m_id;

    // start event loop
    sleep(1);
    ChildReportStat_t report;
    report.id = m_id;
    report.stat = m_perf_stat;
    m_mother->ReportStat(report, m_id);

    event_base_dispatch(m_event_base);

    LOG(INFO) << "Child stop, id " << m_id;
}

void NaughtyKid::OnUpdate(void)
{

}

void NaughtyKid::OnRevCmd(int fd)
{
    MotherSendCmd_t cmd;
    int len;
    if ((len = read(fd, &cmd, sizeof(MotherSendCmd_t))) != sizeof(MotherSendCmd_t)) {
        LOG(ERROR) << "Read from cmd pip error, len " << len;
        return;
    }
    DLOG(INFO) << "Rev cmd, len " << len;
}

void NaughtyKid::Stop(void)
{
    event_base_loopexit(m_event_base, NULL);
    event_base_loopbreak(m_event_base);
    // last, wait thread quit
    Thread::Join();
}


////// thread define

void *ThreadRunWrapper(void *argc)
{
    Thread *obj = static_cast<Thread*>(argc);
    obj->Run();
    return NULL;
}

Thread::Thread(void)
    : m_thread_id(0)
{}

Thread::~Thread(void)
{
    if (m_thread_id != 0) {
        pthread_join(m_thread_id, NULL);
    }
}

int Thread::Start()
{
    if (m_thread_id != 0) {
        LOG(ERROR) << "Thread is running";
        return -1;
    }

    pthread_attr_t attr;
	pthread_attr_init(&attr);
	int ret = pthread_create(&m_thread_id, &attr,ThreadRunWrapper, this);
    if (ret != 0) {
        LOG(ERROR) << "Create thread error, errono : " << errno;
    }
    return ret;
}

void Thread::Join(void)
{
    if (m_thread_id != 0) {
        pthread_join(m_thread_id, NULL);
        m_thread_id = 0;
    }
}

} // namespace perf_robot
