#pragma once
#include <cstdint>

class IMsgOut
{
public:
    virtual ~IMsgOut() = default;
    virtual uint32_t getSize() = 0;

    //read by chunk
    virtual uint8_t *read(uint32_t &) = 0;
    virtual void commit(uint32_t) = 0;
    virtual void cancel();

    // read by bytes
    virtual uint8_t *get(uint32_t) = 0;
};
