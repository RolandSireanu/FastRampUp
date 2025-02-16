#ifndef TYPES_HPP
#define TYPES_HPP
#include <cstdint>

struct Port
{
    int32_t mPort;
};


struct LoadFactor
{
    float mLoadFactor;
};

enum class Protocol
{
    TCP_IP=0,
    UDP=1
};

enum class Execution
{
    SYNC=0,
    ASYNC=1
};

#endif // TYPES_HPP