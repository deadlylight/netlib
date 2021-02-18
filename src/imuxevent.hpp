#pragma once

class IMuxEvent
{
public:
    virtual ~IMuxEvent() = default;
    virtual bool isReady() = 0;
    virtual int getFd() = 0;
    virtual void onError() = 0;
    virtual void onReadable() = 0;
    virtual void onWritable() = 0;
};
