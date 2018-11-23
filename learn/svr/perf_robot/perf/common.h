/*************************************************************************
 > File Name: common.h
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Wed 21 Nov 2018 04:08:16 PM CST
 ************************************************************************/

#ifndef PERF_ROBOT_PERF_COMMON_H
#define PERF_ROBOT_PERF_COMMON_H
#pragma once

#include <stdint.h>

namespace perf_robot {
namespace common {

// ------ define enum
enum PerfRetCode {
    kPerfRetcodeOk = 0,
    kPerfRetcodeNewBaseEventErr = 100,
    kPerfRetcodeNewTimeEventErr,
    kPerfRetcodeNewSigEventErr,
    kPerfRetcodeNewCmdListenerErr,

    kPerfRetcodeOpenMqErr = 600,
    kPerfRetcodeChildMqFull,
    kPerfRetcodeChildMqErr,
    kPerfRetcodeCreateThreadErr,
    kPerfRetcodeNewKidErr,

    kPerfRetcodeChildNotInit = 700,

};


// ----- define struct
#pragma pack(push, 1)

typedef struct PerfStat {

    uint32_t send_count;
    uint32_t receive_count;
    uint32_t error_count;
    uint32_t timeout_count;  // 丢or delay > set_timeout
    uint32_t success_count;

    uint32_t avg_delay_us;
    uint32_t max_delay_us;
    uint32_t min_delay_us;

    uint32_t connected_num;

    PerfStat()
        : send_count(0),receive_count(0),
        error_count(0),timeout_count(0),success_count(0),
        avg_delay_us(0),max_delay_us(0),min_delay_us(0),
        connected_num(0)
    {}
} PerfStat_t;






#pragma pack(pop)
} //namspace common
} //namspace perf_robot
#endif //PERF_ROBOT_PERF_COMMON_H
