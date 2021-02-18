#pragma once
#include <memory>

using namespace std;

class ITcpDataHandler;

class ITcpConnection
{
public:
    virtual ~ITcpConnection() = default;
    virtual void registerDataHandler(shared_ptr<ITcpDataHandler>) = 0;
    virtual IAddr &getLocalAddr() = 0;
    virtual IAddr &getRemoteAddr() = 0;
};
