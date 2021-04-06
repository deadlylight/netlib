#pragma once
#include <cstdint>
#include <memory>

using namespace std;

class IMsgIn
{
public:
    virtual ~IMsgIn() = default;
    virtual uint32_t getSize() = 0;
    virtual shared_ptr<IMsgOut> getMsgOut() = 0;

    // write by chunk
    virtual uint8_t *write(uint32_t) = 0;
    virtual void commit(uint32_t) = 0;
    virtual void cancel() = 0;

    // write by bytes
    virtual put(uint8_t *, uint32_t);
};
