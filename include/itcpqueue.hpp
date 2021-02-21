#pragma once
#include <memory>

using namespace std;

template <class Q, class T>
class ITcpQueue
{
public:
    virtual ~ITcpQueue() = default;
    virtual void push(shared_ptr<T>) = 0;
    virtual shared_ptr<T> pop(bool = false) = 0;
    virtual void move(Q *) = 0;
};

class ITcpConnection;
class ITcpConnectionQueue : public ITcpQueue<ITcpConnectionQueue, ITcpConnection>
{
};

class ITcpMsg;
class ITcpMsgQueue : public ITcpQueue<ITcpMsgQueue, ITcpMsg>
{
};
