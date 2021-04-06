#pragma once
#include <memory>

using namespace std;

class ITcpConn;

class ITcpAccept
{
public:
    virtual ~ITcpAccept() = default;
    virtual bool onTcpConn(shared_ptr<ITcpConn>) = 0;
};
