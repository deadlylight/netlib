#pragma once

class INetIo
{
public:
    virtual ~INetIo() = default;

    virtual int getFd() = 0;
    virtual bool forWrite() = 0;
    virtual bool forRead() = 0;
    virtual void onWrite() = 0;
    virtual void onRead() = 0;
    virtual void onConn() = 0;
    virtual void onDisconn() = 0;
    virtual void onTimeout() = 0;
    virtual void onError() = 0;
};
