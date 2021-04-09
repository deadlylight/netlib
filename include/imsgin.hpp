#pragma once
#include <cstdint>

class IMsgIn
{
public:
    virtual ~IMsgIn() = default;
    virtual uint32_t getSize() = 0;

    //read by chunk
    virtual const void *preRead(uint32_t, uint32_t &) = 0;
    virtual void commitRead(uint32_t) = 0;
    virtual void cancelRead() = 0;

    // read by bytes
    virtual void *get(uint32_t) = 0;
};
