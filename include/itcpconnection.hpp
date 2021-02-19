#pragma once
#include <memory>

using namespace std;

class IMsgIn;
class IMsgOut;

class ITcpConnection
{
public:
    virtual ~ITcpConnection() = default;
    virtual shared_ptr<IMsgIn> readMsg(bool = false) = 0;     // true for non-block
    virtual bool writeMsg(shared_ptr<IMsgOut>) = 0;                // would fail is queue full
    virtual void closeTcpConnection() = 0;
};
