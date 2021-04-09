#pragma once
#include <cstdint>

class IMux
{
public:
    virtual ~IMux() = default;
    virtual void run(uint32_t = 0) = 0;
};
