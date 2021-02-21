#pragma once
#include <memory>

using namespace std;

class ITcpConnectionQueue;
class ITcpMsgQueue;

class CTcpQueueFactory
{
public:
    static shared_ptr<ITcpConnectionQueue> createTcpConnectionQueue();
    static shared_ptr<ITcpMsgQueue> createTcpMsgQueue();
};
