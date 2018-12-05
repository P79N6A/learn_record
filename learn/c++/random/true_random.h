/*************************************************************************
 > File Name: random.h
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Wed 05 Dec 2018 06:46:40 PM CST
 ************************************************************************/

#ifndef _TRUE_RANDOM_H
#define _TRUE_RANDOM_H
#pragma once

#include <stdlib.h>
#include <stdint.h>

namespace common {

#define DECLARCE_UNCOPYABLE(Class)\
private:\
    Class(const Class&);\
    const Class& operator=(const Class&);

class TrueRandom {

    DECLARCE_UNCOPYABLE(TrueRandom);

public:
    TrueRandom();
    ~TrueRandom();

    uint32_t GetUint32();

    uint32_t GetUint32(uint32_t min_random, uint32_t max_random);

    bool GetBuffer(void* buffer, size_t size);
private:
    int32_t m_fd;
};

}
#endif
