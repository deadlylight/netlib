#pragma once
#include <cstdint>

enum
{
    EMuxEventNone = 0,
    EMuxEventRead = 1,
    EMuxEventWrite = 2,
    EMuxEventError = 4,
};

class IMuxEvent
{
public:
    virtual ~IMuxEvent() = default;
    virtual int getFd() = 0;
    virtual uint32_t getMuxEvents() = 0;
    virtual void onError() = 0;
    virtual void onReadable() = 0;
    virtual void onWritable() = 0;
};
