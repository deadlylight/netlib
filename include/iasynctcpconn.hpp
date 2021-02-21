#pragma once
#include <memory>

using namespace std;

class IAsyncTcpConn
{
public:
    virtual ~IAsyncTcpConn() = default;
    virtual void onNewTcpMsg(shared_ptr<IMsg>) = 0;
    virtual void onTcpConnClose(bool) = 0;
    virtual bool writeMsg() = 0;
    virtual void closeTcpConn() = 0;
};
