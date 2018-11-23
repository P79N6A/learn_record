/*************************************************************************
 > File Name: flag.h
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Wed 21 Nov 2018 08:00:17 PM CST
 ************************************************************************/

#ifndef PERF_ROBOT_PERF_FLAG_H
#define PERF_ROBOT_PERF_FLAG_H
#pragma once

#include <gflags/gflags.h>

DECLARE_string(server_ip);
DECLARE_int32(server_port);

DECLARE_int32(perf_work_thread_num);
DECLARE_int32(perf_robot_num);
DECLARE_int32(perf_robot_start_id);
DECLARE_int32(perf_robot_send_per_sec);

DECLARE_int32(report_mq_size);
DECLARE_int32(thread_update_interval);

DECLARE_int32(cmd_port);
DECLARE_int32(cmd_client_num);

DECLARE_string(datasvr_ip);
DECLARE_int32(datasvr_port);

#endif
