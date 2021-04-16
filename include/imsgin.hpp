#pragma once
#include <cstdint>

class IMsgIn
{
public:
    virtual ~IMsgIn() = default;
    virtual uint32_t getSize() = 0;

    virtual const void *preRead(uint32_t) = 0;  // return null if not enough data
    virtual iovec *preReadv(uint32_t &out) = 0;
    virtual void commitRead(uint32_t) = 0;
    virtual void cancelRead() = 0;

    virtual void *get(uint32_t) = 0;    // auto commit, return null if not enough data
};
