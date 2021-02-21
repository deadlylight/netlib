#pragma once
#include <memory>

using namespace std;

class ITcpConnectionQueue;

class ITcpServer
{
public:
    virtual ~ITcpServer() = default;
    virtual void setQueue(shared_ptr<ITcpConnectionQueue>) = 0;
    virtual shared_ptr<ITcpConnectionQueue> getQueue() = 0;
    virtual void shutdownTcpServer() = 0;
};
