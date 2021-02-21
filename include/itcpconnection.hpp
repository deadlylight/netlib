#pragma once
#include <memory>

using namespace std;

class IMsgIn;
class IMsgOut;
class ITcpMsgQueue;

class ITcpConnection
{
public:
    virtual ~ITcpConnection() = default;
    virtual void setQueue(shared_ptr<ITcpMsgQueue>) = 0;
    virtual shared_ptr<ITcpMsgQueue> getQueue() = 0;
    virtual bool writeMsg(shared_ptr<IMsgOut>) = 0;
    virtual void closeTcpConnection() = 0;
};
