#pragma once

class IMuxObject
{
public:
    virtual ~IMuxObject() = default;
    virtual int getFd() = 0;
    virtual bool forRead() = 0;
    virtual bool forWrite() = 0;
    virtual void onRead() = 0;
    virtual void onWrite() = 0;
    virtual void onError() = 0;
    virtual void onTimeoutCheck() = 0;
};
