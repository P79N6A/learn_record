/*************************************************************************
 > File Name: random.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Wed 05 Dec 2018 07:00:45 PM CST
 ************************************************************************/

#include "true_random.h"
#include <unistd.h>
#include <fcntl.h>

namespace  common {

TrueRandom::TrueRandom()
    : m_fd(-1)
{
    m_fd = open("/dev/urandom", O_RDONLY,0);
    if (m_fd < 0) {
        abort();
    }
}

TrueRandom::~TrueRandom()
{
    close(m_fd);
    m_fd = -1;
}

uint32_t TrueRandom::GetUint32()
{
    uint32_t random = -1;
    GetBuffer(&random, sizeof(random));
    return random;
}

uint32_t TrueRandom::GetUint32(uint32_t min_random, uint32_t max_random)
{
    uint32_t ramdom = GetUint32();
    return (ramdom + min_random) % max_random;
}

bool TrueRandom::GetBuffer(void* buffer, size_t size)
{
    return (read(m_fd, buffer, size) == static_cast<size_t>(size));
}

}
