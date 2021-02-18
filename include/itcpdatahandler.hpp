#pragma once
#include <memory>

using namespace std;

class ITcpConnection;

class ITcpDataHandler
{
public:
    virtual ~ITcpDataHandler() = default;
    virtual void setTcpConnection(shared_ptr<ITcpConnection>) = 0;
    virtual void onData() = 0;
    virtual void onError() = 0;
};