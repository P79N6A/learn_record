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

namespace perf_robot {

class Robot {
public:

    Robot(uint32_t id);
    ~Robot();

private:
    uint32_t m_id;

};

} // namespace perf_robot
#endif //PERF_ROBOT_PERF_ROBOT_H
