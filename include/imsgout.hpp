#pragma once
#include <cstdint>
#include <memory>

using namespace std;

class IMsgIn;

class IMsgOut
{
public:
    virtual ~IMsgOut() = default;
    virtual uint32_t getSize() = 0;
    virtual shared_ptr<IMsgIn> getMsgIn() = 0;

    // write by chunk
    virtual void *preWrite(uint32_t, uint32_t &) = 0;
    virtual void commitWrite(uint32_t) = 0;
    virtual void cancelWrite() = 0;

    // write by bytes
    virtual void put(void *, uint32_t) = 0;

    virtual void merge(IMsgIn &) = 0;
};
