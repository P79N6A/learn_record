/*************************************************************************
 > File Name: msg_define.h
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Wed 21 Nov 2018 03:48:00 PM CST
 ************************************************************************/

#ifndef PERF_ROBOT_PERF_MSG_DEFINE_H
#define PERF_ROBOT_PERF_MSG_DEFINE_H
#pragma once

#include "common.h"
#include <stdint.h>

//  虎妈与熊孩子间的消息定义
//  虎妈与熊孩子通信
//      虎妈 -> 孩子 pipe, 马上干活
//      孩子 -> 虎妈 mq， 排队汇报数据
//
namespace perf_robot {
#pragma pack(push, 1)

typedef struct ChildReportStat {

    int thread_id;
    common::PerfStat_t stat;

    ChildReportStat()
        :thread_id(-1), stat()
    {}
} ChildReportStat_t;

typedef struct MotherSendCmd {
    uint8_t cmd;
    union {
        uint32_t send_per_sec;
    };
} MotherSendCmd_t;

#pragma pack(pop)
} //namespace perf_robot

#endif //PERF_ROBOT_PERF_MSG_DEFINE_H
