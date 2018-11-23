/*************************************************************************
 > File Name: flag.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Wed 21 Nov 2018 07:55:18 PM CST
 ************************************************************************/

#include "flag.h"

// 压测服务器
DEFINE_string(server_ip, "127.0.0.1", "connect server's ip");
DEFINE_int32(server_port, 8888, "server port");

// 压力设置
DEFINE_int32(perf_work_thread_num, 2, "work threads num");
DEFINE_int32(perf_robot_num, 200, "total robot number");
DEFINE_int32(perf_robot_start_id, 1, "robot start id");
DEFINE_int32(perf_robot_send_per_sec, 10, "send speed /s");

//内部设置
DEFINE_int32(report_mq_size, FLAGS_perf_work_thread_num * 3, "mq for child report stat to mother");
DEFINE_int32(thread_update_interval, 100, "thread update robot interval， ms");


//cmd 监听
DEFINE_int32(cmd_port, 8889, "cmd listen port");
DEFINE_int32(cmd_client_num, 2, "cmd listen client limit");

//datareport
//if set, will report stat to svr
DEFINE_string(datasvr_ip, "", "datacollect svr ip");
DEFINE_int32(datasvr_port, 0, "datacollect svr port");

